#include "blather.h"

int server_finished = 0;

void handle_SIGINT(int sig_num) {
    server_finished = 1;
}

void handle_SIGTERM(int sig_num) {
    server_finished = 1;
}

int main(int argc, char * argv[]) {
    // Ensure proper usage, exit if not
    if (argc < 2) {
        printf("Usage: %s <name-of-server>\n", argv[0]);
        exit(1);
    }

    // Establish sigaction to handle termination of program
    // Alert terminal that this step is finished
    struct sigaction server_sa = {};
    sigemptyset(&server_sa.sa_mask);
    server_sa.sa_flags = SA_RESTART;
    server_sa.sa_handler = handle_SIGTERM;
    sigaction(SIGTERM, &server_sa, NULL);
    server_sa.sa_handler = handle_SIGINT;
    sigaction(SIGINT, &server_sa, NULL);
    printf("signal handlers established\n");

    // Set up new server
    // Create server_t, establish server_name with arguments passed into process
    // Alert server terminal of actions, and attempt to start new server
    server_t server = {};
    char new_server_name[MAXPATH];

    snprintf(new_server_name, MAXNAME, "%s", argv[1]);
    printf("server_start()\n");
    server_start(&server, new_server_name, DEFAULT_PERMS);
    printf("server_start(): end\n");

    // Major function of server: wait for input from sources, and then handle it
    // Use server_check_sources() to see if any data has 'arrived'
    while (server_finished == 0) {
        server_check_sources(&server);
        // If server.join_data has been changed, handle the new join
        if (server_join_ready(&server) > 0) {
            printf("server_handle_join()\n");
            int j_ret = server_handle_join(&server);
            if (j_ret != 0) {
                printf("server_handle_join(): failed\n");
            }
            else {
                printf("server_handle_join(): succeed\n");
            }
        }
        // Check each client in the server.client[] array
        // If any have data ready, handle the data
        for (int i = 0; i < server.n_clients; i++) {
            if (server_client_ready(&server, i) > 0) {
                printf("server_handle_client()\n");
                int c_ret = server_handle_client(&server, i);
                if (c_ret != 0) {
                    printf("server_handle_client(): failed\n");
                }
                else {
                    printf("server_handle_client(): succeed\n");
                }
            }
        }
        /*for (int i = 0; i < server.n_clients; i++) {
            printf("%d %s %d %s\n", server.client[i].to_client_fd, server.client[i].to_client_fname, server.client[i].to_server_fd, server.client[i].to_server_fname);
        }*/
    }

    // If while loop has ended, time for server to shutdown
    // Call shutdown_server, alert server terminal
    printf("server_shutdown()\n");
    server_shutdown(&server);
    printf("server_shutdown(): end\n");

    return 0;
}
