#include "commando.h"

// Print everything in a cmdcol object, nicely formatted
void cmdcol_print(cmdcol_t *col) {
  // Print the header
  printf("%-4s %-9s %4s %10s %4s %s\n","JOB","#PID","STAT","STR_STAT","OUTB","COMMAND");

  // for loop to iterate through each cmd stored in the cmdcol object
  // Each member that is printed is formatted in size to match header
  for (int i  = 0; i < col->size; i++) {
    printf("%-4d ",i);
    printf("#%-8d ",col->cmd[i]->pid);
    printf("%4d ",col->cmd[i]->status);
    printf("%10s ",col->cmd[i]->str_status);
    printf("%4d",col->cmd[i]->output_size);
    // Interior for loop to print each char * argument from argv
    for (int j = 0; col->cmd[i]->argv[j] != NULL; j++) {
      printf(" %s",col->cmd[i]->argv[j]);
    }
    printf("\n");
  }
}

// Add a new cmd object to the cmdcol object
void cmdcol_add(cmdcol_t *col, cmd_t *cmd) {
  // Check if cmdcol is full
  if (col->size == MAX_CMDS) {
    printf("Danger, danger, full cmdcol exists.\n");
  } else {
  // Otherwise, add cmd object to cmdcol and increase cmdcol->size
    col->cmd[col->size] = cmd;
    col->size++;
  }
}

// Update each cmd object in the cmdcol object
void cmdcol_update_state(cmdcol_t *col, int nohang) {
  // for loop to iterate through cmdcol object
  for (int i = 0; i < col->size; i++) {
    // Use cmd_update_state() to update each individual cmd object
    // nohang variable determines if program should wait for child process to finish
    cmd_update_state(col->cmd[i], nohang);
  }
}

// free each cmd object in the cmdcol object
void cmdcol_freeall(cmdcol_t *col) {
  // for loop to free each cmd object invidivually
  for (int i = 0; i < col->size; i++) {
    // Use cmd_free() to dynamically free all space allocated to each cmd object
    cmd_free(col->cmd[i]);
  }
}
