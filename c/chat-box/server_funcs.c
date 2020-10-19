#include "blather.h"

// Return client_t struct from server indicated by index idx
client_t * server_get_client(server_t * server, int idx) {
    // Simply return the client_t struct by accessing server.client[] array
    // If idx is > MAXCLIENTS, problems happen
    return &server->client[idx];
}

// Start server indicated by server_name
void server_start(server_t * server, char * server_name, int perms) {
    // User a char[] to hold the server_name appended by .fifo
    char fifo_name[MAXPATH];
    // Add .fifo to the server_name
    snprintf(fifo_name, MAXPATH, "%s.fifo", server_name);
    // Ensure no previous instances of the fifo exist, and remove them if they do
    remove(fifo_name);
    // Start the fifo using the passed in perms
    int f_ret = mkfifo(fifo_name, perms);
    if (f_ret < 0) {
        printf("Server fifo not made\n");
    }
    // Store the fifo FD in the server.join_fd field, with O_RDWR perms
    server->join_fd = open(fifo_name, O_RDWR);
    // Set server defaults to allow clients to join
    server->n_clients = 0;
    snprintf(server->server_name, MAXPATH, "%s", fifo_name);
}

// Shutdown the server, sending a shutdown message to each client
void server_shutdown(server_t * server) {
    // Create the mesg_t struct needed to send messages
    // Fill it with appropriate information
    mesg_t shutdown_mesg = {};
    char * shutdown_message = "!!! server is shutting down !!!\n";
    snprintf(shutdown_mesg.body, MAXLINE, "%s", shutdown_message);
    shutdown_mesg.kind = BL_SHUTDOWN;
    // Iterate through the server->client[] array, sending the same message to each one
    server_broadcast(server, &shutdown_mesg);
    // Close the server FIFO
    remove(server->server_name);
    close(server->join_fd);
}

// Add a new client to the server using information from the join parameter
int server_add_client(server_t * server, join_t * join) {
    // Check if maxclients has been reached, return non-zero if yes
    if (server->n_clients == MAXCLIENTS) {
        return -1;
    }
    else {
        // Create a new client struct to filled in with information
        client_t new_client = {};
        // Copy over information from join into new_client
        snprintf(new_client.name, MAXPATH, "%s", join->name);
        snprintf(new_client.to_client_fname, MAXPATH, "%s", join->to_client_fname);
        snprintf(new_client.to_server_fname, MAXPATH, "%s", join->to_server_fname);

        // Establish a FIFO to send information to the client from the server
        // And another FIFO to send information from the client to the server
        new_client.to_client_fd = open(new_client.to_client_fname, O_RDWR);
        new_client.to_server_fd = open(new_client.to_server_fname, O_RDWR);

        // printf("%d %s %d %s\n", new_client.to_client_fd, new_client.to_client_fname, new_client.to_server_fd, new_client.to_server_fname);

        // Initialize the new_client's data ready to receive messages
        // Then copy the new_client into the server's client[] array
        // And increment the n_clients counter to account for the new client
        new_client.data_ready = 0;
        server->client[server->n_clients] = new_client;
        server->n_clients++;

        // Create new join_mesg and broadcast to all clients to notify of new client
        mesg_t join_mesg = {};
        snprintf(join_mesg.body, MAXLINE, "-- %s JOINED --\n", new_client.name);
        join_mesg.kind = BL_JOINED;
        // printf("msg kind %d %d\n", join_mesg.kind, BL_JOINED);
        server_broadcast(server, &join_mesg);

        // Return 0 as success
        return 0;
    }
}

// Remove a client from the server client[] array with the given index
// Close the FIFOs associated with that client
// Notify all other clients of the departure
int server_remove_client(server_t * server, int idx) {
    client_t * rem_client = server_get_client(server, idx);

    // Close the file descriptors associated with the given client's FIFOs
    close(rem_client->to_client_fd);
    close(rem_client->to_server_fd);

    // Decrement n_clients to reflect one client departing
    // 'Remove' the client in the client array by writing over it
    // Fill in the gap by moving each client down one index
    server->n_clients--;
    for (int i = idx; i < server->n_clients; i++) {
        server->client[i] = server->client[i+1];
    }

    // Return 0 if successful removal has occurred
    return 0;
}

// Send a mesg_t to each client
// Use the to_client_fd FIFO associated with each client
int server_broadcast(server_t * server, mesg_t * mesg) {
    for (int i = 0; i < server->n_clients; i++) {
        client_t * s_client = server_get_client(server, i);
        int ret = write(s_client->to_client_fd, mesg, sizeof(mesg_t));
        if (ret < 0) {
            printf("Error with broadcast\n");
        }
    }
    return 0;
}

// Use poll to check all clients-to-server FIFOs and the server's join FIFO
// If any have data waiting to be read by the server, change the _ready
// value associated with the FIFO so the server process can handle the information
void server_check_sources(server_t * server) {
    // Create a poll struct equal to n_clients + 1
    // The extra one is to handle the server's join_fd
    struct pollfd spfd[server->n_clients+1];

    // Add the appropriate fd's to each of the poll array's elements
    // The join_fd gets put at the end of the queue
    for (int i = 0; i < server->n_clients; i++) {
        spfd[i].fd = server->client[i].to_server_fd;
        spfd[i].events = POLLIN;
        spfd[i].revents = 0;
    }
    spfd[server->n_clients].fd = server->join_fd;
    spfd[server->n_clients].events = POLLIN;
    spfd[server->n_clients].revents = 0;

    // Use the poll() call to look for any fd's that are ready
    // Also checks the server's join_fd
    printf("Polling for Data\n");
    int ret = poll(spfd, server->n_clients+1, -1);
    if (ret < 0) {
        printf("An error happening when poll()'ing\n");
    }
    // Iterate through the spfd array to determine which clients have data ready
    // If the client or server join_fd has sent data, increment the join_ready
    // or client[i].data_ready to indicate an event has happened
    for (int i = 0; i < server->n_clients+1; i++) {
        if (spfd[i].revents & POLLIN) {
            if (i == (server->n_clients)) {
                server->join_ready = 1;
            }
            else {
                server->client[i].data_ready = 1;
            }
        }
    }
}

// Return the join_ready field from the server
int server_join_ready(server_t * server) {
    // Just used to check on the join_ready value
    // Not totally sure why this is used
    // Checking server->join_ready is just as easy to do from whatever calls this
    // Oh well
    return server->join_ready;
}

// Handle a join request to the server
// Only called after server_join_ready, so it will always be 'safe'
int server_handle_join(server_t * server) {
    // Create a join_t struct to load in the new join data
    // Then read from the server's join_fd to get the information
    join_t new_join = {};
    int ret = read(server->join_fd, &new_join, sizeof(join_t));
    if (ret < 0) {
        printf("Error when trying to read join_t\n");
    }

    // Using this information, call server_add_client with the join information
    // Reset server's join_ready to 0 to indicate it can handle another join now
    int jret = server_add_client(server, &new_join);
    server->join_ready = 0;

    // If there was an issue adding the client, print an error message
    // Return 1 for a problem
    if (jret != 0) {
        printf("New client could not be added\n");
        return 1;
    }

    printf("%s joined\n", new_join.name);

    // Return 0 if all good
    return 0;
}

// Same as server_join_ready, but check's if a client at the given idx has data
int server_client_ready(server_t * server, int idx) {
    // Still not totally sure why we call this and not just use the call
    // to server->client[idx].data_ready from wherever this is calling from
    return server->client[idx].data_ready;
}

// Receive a message from a client
// Only called after server_client_ready, so it will always be 'safe'
int server_handle_client(server_t * server, int idx) {
    // Create new mesg_t to handle the message coming from the client
    mesg_t new_mesg = {};
    // Read the message from the client
    int ret = read(server->client[idx].to_server_fd, &new_mesg, sizeof(mesg_t));
    if (ret < 0) {
        printf("Error when trying to read mesg_t from client\n");
    }
    else {
        // Set client's data_ready value to 0, indicating more data can be read
        server->client[idx].data_ready = 0;
        // Test message type and take appropriate action depending on type
        if (new_mesg.kind == BL_MESG) {
            printf("%s sent: %s\n", new_mesg.name, new_mesg.body);
            // If a simple message is sent, broadcast this to all clients
            server_broadcast(server, &new_mesg);
            return 0;
        }
        else if (new_mesg.kind == BL_DEPARTED) {
            printf("%s departed\n", new_mesg.name);
            // If a departed message has been received, take action to remove client
            server_remove_client(server, idx);
            // Construct a depart message and broadcast to all other clients
            mesg_t depart_mesg = {};
            snprintf(depart_mesg.body, MAXLINE, "-- %s DEPARTED --\n", new_mesg.name);
            depart_mesg.kind = BL_DEPARTED;
            server_broadcast(server, &depart_mesg);
            return 0;
        }
    }

    // Return 1 if a message was not read or type was not recognized
    return 1;
}
