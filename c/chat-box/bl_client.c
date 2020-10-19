#include "blather.h"

simpio_t simpio_actual;
simpio_t *simpio = &simpio_actual;

client_t this_client;
client_t *client = &this_client;

pthread_t client_thread;
pthread_t server_thread;

// Function to handle client input
// Lets client continue to input data uninterrupted
// And also keeps the terminal neat by not printing randomly
void * client_print(void *arg) {
    int count = 1;
    // Continues until EOF (or a EOF signal) is reached
    while (!simpio->end_of_input) {
        simpio_reset(simpio);
        iprintf(simpio, "");
        while (!simpio->line_ready && !simpio->end_of_input) {
            simpio_get_char(simpio);
        }
        // After a line is input, capture the information and send to the server
        if (simpio->line_ready) {
            // Use mesg_t struct to send information
            // Sends message BL_MESG type
            // After filling in mesg_t fields, write to server fifo
            mesg_t new_mesg = {};
            new_mesg.kind = BL_MESG;
            snprintf(new_mesg.name, MAXNAME, "%s", client->name);
            snprintf(new_mesg.body, MAXLINE, "%s", simpio->buf);
            int m_ret = write(client->to_server_fd, &new_mesg, sizeof(mesg_t));
            if (m_ret < 0) {
                printf("Error sending message\n");
            }
            count++;
        }
    }
    // After EOF is reached, send a departure message
    // This mesg_t struct has the .kind field of BL_DEPARTED
    // After filling in mesg_t fields, write to server fifo
    mesg_t dep_mesg = {};
    dep_mesg.kind = BL_DEPARTED;
    snprintf(dep_mesg.name, MAXNAME, "%s", this_client.name);
    int d_ret = write(client->to_server_fd, &dep_mesg, sizeof(mesg_t));
    if (d_ret < 0) {
        printf("YOU CAN'T LEA-...I mean, error upon departing\n");
    }

    // Cancel the server_thread to facillitate ending the bl_client process
    pthread_cancel(server_thread);

    return NULL;
}

// Function to handle receiving information from the server
// Uses infinite loop to just consistently read the ->to_client_fd
// Upon receiving data, checks the type and handles it appropriately
void * server_print(void *arg) {
    while (1) {
        mesg_t rec_mesg = {};
        int s_ret = read(client->to_client_fd, &rec_mesg, sizeof(mesg_t));
        if (s_ret < 0) {
            printf("Error receiving messages\n");
        }
        // Regular message is printed with name and body
        if (rec_mesg.kind == BL_MESG) {
            iprintf(simpio, "[%s] : %s\n", rec_mesg.name, rec_mesg.body);
        }
        // Departures and joins are already formatted, just need to print
        else if (rec_mesg.kind == BL_DEPARTED || rec_mesg.kind == BL_JOINED) {
            iprintf(simpio, "%s", rec_mesg.body);
        }
        // If a shutdown message is received, prepare to close client
        // Print the message, and close the client thread, to end bl_client process
        else if (rec_mesg.kind == BL_SHUTDOWN) {
            iprintf(simpio, "%s", rec_mesg.body);
            pthread_cancel(client_thread);
            return NULL;
        }
    }

    return NULL;
}

int main(int argc, char * argv[]) {
    // Ensure proper usage, exit if not
    if (argc < 3) {
        printf("Usage: %s <name-of-server> <name-of-client>\n", argv[0]);
        exit(1);
    }

    // Capture name of server and open access to it
    char server_to_join[MAXPATH];
    snprintf(server_to_join, MAXPATH, "%s.fifo", argv[1]);
    int server_fd = open(server_to_join, O_RDWR);

    // Create a join_t struct to send to the server
    // Use the command argument to determine name of the client
    // Create a unique name for the .to_client and .to_server FIFOs
    join_t this_join = {};
    snprintf(this_join.name, MAXNAME, "%s", argv[2]);
    snprintf(this_join.to_client_fname, MAXPATH, "%d-%s-to_client.fifo", getpid(), this_join.name);
    snprintf(this_join.to_server_fname, MAXPATH, "%d-%s-to_server.fifo", getpid(), this_join.name);

    // Begin filling in the local client's information, copying from the join_t
    snprintf(this_client.name, MAXNAME, "%s", this_join.name);
    snprintf(this_client.to_client_fname, MAXPATH, "%s", this_join.to_client_fname);
    snprintf(this_client.to_server_fname, MAXPATH, "%s", this_join.to_server_fname);

    // Ensure the FIFOs didn't already exist
    // Then open the two FIFOs specific to this client
    remove(this_client.to_client_fname);
    remove(this_client.to_server_fname);
    int m1_ret = mkfifo(this_client.to_client_fname, DEFAULT_PERMS);
    if (m1_ret < 0) {
        printf(".to_client FIFO not made\n");
    }
    int m2_ret = mkfifo(this_client.to_server_fname, DEFAULT_PERMS);
    if (m2_ret < 0) {
        printf(".to_server FIFO not made\n");
    }

    // Open the new FIFOs
    this_client.to_client_fd = open(this_client.to_client_fname, O_RDWR);
    this_client.to_server_fd = open(this_client.to_server_fname, O_RDWR);

    // Send the new join_t to the server to add this client to the server's list
    int j_ret = write(server_fd, &this_join, sizeof(join_t));
    if (j_ret < 0) {
        printf("Failed joining server\n");
        exit(1);
    }

    // printf("%d %s %d %s\n", this_client.to_client_fd, this_client.to_client_fname, this_client.to_server_fd, this_client.to_server_fname);

    // Create client specific prompt for the printer
    // Then do the wonderful simpio things provided for us
    char n_prompt[MAXNAME];
    snprintf(n_prompt, MAXNAME+3, "%s%s", this_join.name, PROMPT);
    simpio_set_prompt(simpio, n_prompt);
    simpio_reset(simpio);
    simpio_noncanonical_terminal_mode();

    // Create each client and server thread, and send the _print functions to them
    // Join each thread to make it active
    pthread_create(&client_thread,   NULL, client_print,   NULL);
    pthread_create(&server_thread, NULL, server_print, NULL);
    pthread_join(client_thread, NULL);
    pthread_join(server_thread, NULL);

    // Send things back to normal
    simpio_reset_terminal_mode();
    printf("\n");

    // Close all the FIFOs and remove the ones created by this process
    close(server_fd);
    close(this_client.to_client_fd);
    close(this_client.to_server_fd);
    remove(this_client.to_client_fname);
    remove(this_client.to_server_fname);
    return 0;
}
