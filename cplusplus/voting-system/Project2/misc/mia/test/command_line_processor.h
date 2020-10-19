#ifndef COMMAND_LINE_PROCESSOR_H_
#define COMMAND_LINE_PROCESSOR_H_

// Author: Philip Siedlecki, University of Minnesota
// Copyright 2018

#include <stdio.h>
#include <string.h>
#include <list>

// 2097152 argc size

const int MAX_INPUT = 3;  // the maximum number of input args to a function

namespace image_tools {

class CommandLineProcessor {
 public:
  // This should handle all calls
  CommandLineProcessor(int num, char **cmd);

  void PrintCommands();

 private:
  // find file extensions in the input string
  // return true if the extrensions are present
  bool IsFile(char *buf);

  // return true if buff contains only digits and '.' values
  bool IsFloat(char *buf);
  
  // Extract each command and place into a struct list
  void ExtractCommands(int num, char ** cmd);

  // Print off all command in the command_list_
  

  // This is for all commands, each command will have a name
  // and following arguments
  struct Command {
    char name[255];   // 255 char is max filename length
    float input[MAX_INPUT];
    int num_args;
  };

  std::list<Command> command_list_;  // list of all commands in order
};

}  // namepsace image_tools

#endif  // COMMAND_LINE_PROCESSOR_H_
