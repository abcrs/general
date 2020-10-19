#include "commando.h"

// cmd_print helper function to print a cmd output
void cmd_print(cmd_t *cmd);

int main(int argc, char*argv[]) {
  // Turn off output buffering
  setvbuf(stdout, NULL, _IONBF, 0);

  // Set echo status
  int echo = 0;
  char *echo_str = "COMMAND_ECHO";

  // Check if --echo exists from terminal input
  if (argc > 1) {
    if (strcmp(argv[1],"--echo") == 0) {
      echo = 1;
    }
  }
  // Check if COMMAND_ECHO environment has been set to non-NULL
  if (getenv(echo_str) != NULL) {
    echo = 1;
  }

  cmdcol_t *cmdcol = malloc(sizeof(cmdcol_t));
  cmdcol->size = 0;

  // while loop executes majority of code
  while(1) {
    // Print the prompt
    printf("@> ");

    // input_buf stores user input
    char input_buf[MAX_LINE];
    char * eof = fgets(input_buf, MAX_LINE, stdin);
    // If eof is NULL, End of input has been reached, end loop
    if (eof == NULL) {
      printf("\nEnd of input\n");
      break;
    }

    // If echo is set, print input back to the user
    if (echo == 1) {
      printf("%s",input_buf);
    }

    // Use parse_into_tokens() to determine user inputted tokens
    char *tokens[ARG_MAX+1];
    int *ntok = malloc(sizeof(int));
    parse_into_tokens(input_buf, tokens, ntok);
    free(ntok);

    // Check what the tokens are
    if (tokens[0] != NULL) {
      if (strcmp(tokens[0], "exit") == 0) {
      // exit means end of input, end loop
        break;

      } else if (strcmp(tokens[0], "help") == 0) {
      // help prints possible commands and descriptions of them
        printf("COMMANDO COMMANDS\n");
        printf("help               : show this message\n");
        printf("exit               : exit the program\n");
        printf("list               : list all jobs that have been started giving information on each\n");
        printf("pause nanos secs   : pause for the given number of nanseconds and seconds\n");
        printf("output-for int     : print the output for given job number\n");
        printf("output-all         : print output for all jobs\n");
        printf("wait-for int       : wait until the given job number finishes\n");
        printf("wait-all           : wait for all jobs to finish\n");
        printf("command arg1 ...   : non-built-in is run as a job\n");

      } else if (strcmp(tokens[0], "list") == 0) {
      // list prints list of commands that have been inputted
        cmdcol_print(cmdcol);

      } else if (strcmp(tokens[0], "pause") == 0){
      // pause puts program on hold for determined period of time
        char * ptr;
        // Use strtol() for long input, use automatic casting for int input
        pause_for(strtol(tokens[1],&ptr,10), *tokens[2]-'0');

      } else if (strcmp(tokens[0], "output-for") == 0){
      // output-for prints output for one specific command
        cmd_print(cmdcol->cmd[*tokens[1]-'0']);

      } else if (strcmp(tokens[0], "output-all") == 0){
      // output-all prints output for all commands
        for (int i = 0; i < cmdcol->size; i++) {
          // Use cmd_print() to print each output one at a time
          cmd_print(cmdcol->cmd[i]);
        }

      } else if (strcmp(tokens[0], "wait-for") == 0){
      // wait-for waits for one specific command to finish
        if (cmdcol->cmd[*tokens[1]-'0']->finished != 1) {
          // If command is not finished, call cmd_update_state to wait for it
          // Signify waiting by sending DOBLOCK variable
          cmd_update_state(cmdcol->cmd[*tokens[1]-'0'],DOBLOCK);
        }

      } else if (strcmp(tokens[0], "wait-all") == 0){
      // wait-all waits for all commands to finish
        for (int i = 0; i < cmdcol->size; i++) {
          // Call cmd_update_state on each individual command
          // Use DOBLOCK again to signify waiting for commands to finish
          if (cmdcol->cmd[i]->finished != 1) {
            cmd_update_state(cmdcol->cmd[i],DOBLOCK);
          }
        }

      } else {
      // Only other non-NULL input would be a new command
      // Call cmd_new() to instantiate a new cmd_t object
      // Add the new object to cmdcol, and start it
        cmd_t *new_cmd = cmd_new(tokens);
        cmdcol_add(cmdcol, new_cmd);
        cmd_start(cmdcol->cmd[cmdcol->size-1]);
      }
    }
    // Call cmdcol_update_state to update all commands
    // Variable NOBLOCK signifies not waiting for completion, just want update
    cmdcol_update_state(cmdcol, NOBLOCK);
  }

  // After loop is done, free all allocated memory with cmdcol_freeall()
  cmdcol_freeall(cmdcol);
  // Finally, free cmdcol from all the weight is has been under
  free(cmdcol);

  return 0;
}

void cmd_print(cmd_t *cmd) {
  // Print header for command output
  printf("@<<< Output for %s[#%d] (%d bytes):\n",cmd->name, cmd->pid, cmd->output_size);
  printf("----------------------------------------\n");
  if (cmd->output == NULL) {
    // If output is still NULL, command hasn't finished and output isn't read
    printf("%s[#%d] : output not ready\n",cmd->name, cmd->pid);
  } else {
    // Store output (which is void*) in char* to be printed
    char * s = cmd->output;
    printf("%s",s);
  }
  // Print footer
  printf("----------------------------------------\n");
}
