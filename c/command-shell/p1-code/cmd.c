#include "commando.h"

#define PREAD 0
#define PWRITE 1

// Initialize new cmd_t struct, and initialize all of the values
cmd_t * cmd_new(char * argv[]) {
  // malloc appropriate size
  cmd_t * new_cmd = malloc(sizeof(cmd_t));
  // Iterate through the passed in argv char * array
  // Use strdup to create a new copy of each char *, store in new_cmd->argv
  int i;
  for(i = 0; argv[i] != NULL; i++) {
    new_cmd->argv[i] = strdup(argv[i]);
  }
  // Add NULL as last member of new_cmd->argv
  new_cmd->argv[i] = NULL;
  // Use strcpy to copy the command into new_cmd->name
  strcpy(new_cmd->name,argv[0]);

  // Initialize all other variables as per requirements
  new_cmd->finished = 0;
  snprintf(new_cmd->str_status,5,"INIT");
  new_cmd->pid = -1;
  new_cmd->out_pipe[0] = -1;
  new_cmd->out_pipe[1] = -1;
  new_cmd->status = -1;
  new_cmd->output = NULL;
  new_cmd->output_size = -1;

  // Return newly created cmd_t object
  return new_cmd;
}

// Properly deallocate all memory in a cmd_t object
void cmd_free(cmd_t *cmd) {
  // Don't free the output if not NULL
  if (cmd->output != NULL) {
    free(cmd->output);
  }

  // Free each member of the cmd->argv array
  int i = 0;
  char* c = cmd->argv[i];
  // Stop free-ing when NULL is reached
  while (c != NULL) {
    free(cmd->argv[i]);
    i++;
    // Reassign c
    c = cmd->argv[i];
  }

  // Free the *cmd object itself
  free(cmd);
}

// Start the process determined by the cmd
void cmd_start(cmd_t *cmd) {
  // Update status to running
  snprintf(cmd->str_status,4,"RUN");

  // Create a pipe to capture output
  pipe(cmd->out_pipe);
  // For the process and store the child pid
  cmd->pid = fork();
  // Child commands:
  if (cmd->pid == 0) {
    // Change child STDOUT_FILENO to write to the pipe, close other end of pipe
    dup2(cmd->out_pipe[PWRITE], STDOUT_FILENO);
    close(cmd->out_pipe[PREAD]);
    // Start the new process using execvp
    execvp(cmd->name, cmd->argv);
  } else {
    // Close parent write side of pipe
    close(cmd->out_pipe[PWRITE]);
  }
}

// Check the status of a cmd process
// If the child process is finished, update data accordingly
void cmd_update_state(cmd_t *cmd, int block) {
  // If already finished, update nothing
  if (cmd->finished != 1) {
    int status;
    // waitpid() returns child pid if it is finished
    pid_t pid = waitpid(cmd->pid, &status, block);
    if (pid == cmd->pid) {
      // If child is finished, use WIFEXITED to determine status
      if (WIFEXITED(status) != 0) {
        // Update data accordingly with as finished
        cmd->status = WEXITSTATUS(status);
        cmd->finished = 1;
        snprintf(cmd->str_status,8,"EXIT(%d)",cmd->status);

        // Retrieve the output from the child process
        cmd_fetch_output(cmd);

        // Alert user of process finished
        printf("@!!! %s[#%d]: %s\n", cmd->name, cmd->pid, cmd->str_status);
      }
    } else if (pid == -1) {
      // Something bad happened, kill it before it becomes dangerous
      exit(1);
    }
  }
}

// Retrieve output from child process
void cmd_fetch_output(cmd_t *cmd) {
  // Error check, if not finished print message
  if (cmd->finished == 0) {
    printf("%s[#%d] not finished yet\n",cmd->name,cmd->pid);
  } else {
  // If finished, call read_all to get data and then close the pipe
    cmd->output = read_all(cmd->out_pipe[PREAD], &cmd->output_size);
    close(cmd->out_pipe[PREAD]);
  }
}

// Print the ouput stored in the cmd object
void cmd_print_output(cmd_t *cmd) {
  // Error check - if output still NULL, print message
  if (cmd->output == NULL) {
    printf("%s[%d] : output not ready\n",cmd->name, cmd->pid);
  } else {
  // If output isn't NULL, write using STDOUT_FILENO and outout_size
    write(STDOUT_FILENO, cmd->output, cmd->output_size);
  }
}

// Read all data from a child process
char *read_all(int fd, int *nread) {
  // Initialize values and char *buff that will hold output
  int cur_pos = 0;
  int max_size = 1024;
  char *buff = malloc(max_size*sizeof(char));

  // Loop until break called, which happens at end of file
  while(1) {
    // If cur_pos is greater than max_size, file has more data
    // But buff is not big enough to hold more, so realloc with more space
    if (cur_pos >= max_size) {
      max_size = max_size * 2;
      buff = realloc(buff, max_size);
      if (buff == NULL) {
        // Problems happened if buff ruined, exit quickly
        printf("Big boom boom coming down the pipe\n");
        exit(1);
      }
    }

    // max_read updates each time, so buff does not get overfill
    int max_read = max_size - cur_pos;
    // read_total will say how many bytes were read
    // read() will take information from fd (which is from the pipe)
    // and store it in buff, starting at cur_pos. Will only read max_read bytes
    int read_total = read(fd, buff+cur_pos, max_read);

    // If read_total is less than max_read or is equal to 0
    // End of file has been reached. Update cur_pos and end while loop
    if (read_total == 0 || read_total < max_read) {
      cur_pos += read_total;
      break;
    } else if (read_total == -1) {
    // read_total less than 0 means something bad has happened
      printf("Bad juju\n");
      exit(1);
    }

    // Update cur_pos with the number of bytes read
    cur_pos += read_total;
  }

  // Final byte added, the \0 character, may need additional space
  // Reallocate with slightly more space if necessary
  if (cur_pos >= max_size) {
    max_size = max_size + 1;
    buff = realloc(buff,max_size);
  }
  // Enter the terminate character
  buff[cur_pos] = '\0';

  // Update pointer value, allowing the output_size to be updated
  *nread = cur_pos;

  // Return the output
  return buff;
}
