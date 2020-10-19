// Author: Philip Siedlecki, University of Minnesota
// Copyright 2018

#include "command_line_processor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <list>

namespace image_tools {
  CommandLineProcessor::CommandLineProcessor(int num, char **cmd) {
    ExtractCommands(num, cmd);
    // take each command in the list and check that the individual
    // function requirements are met
  }

  bool CommandLineProcessor::IsFile(char * buf) {
    char * probe = buf;  // point to the start
    while (*probe != '\0') {
      probe++;
    }
    // probe is now at the end of our input string
    probe -= 4;  // garbage.png_ -> garbage_.png (probe == _)
    return strcmp(probe, ".png") == 0;
  }

  bool CommandLineProcessor::IsFloat(char * buf) {
    // all characters should be 0, 1, .. 9 or .
    // ascii range to check 48 = '0' -> 57 = '9', 46 = '.'
    char * probe = buf;
    while (*probe != '\0') {  // check whole string
      if (*probe < 46 || *probe > 57 || *probe == 47) {
	return false;
      }
      probe++;
    }
    return true;
  }
  
  void CommandLineProcessor::ExtractCommands(int num, char **cmd) {
    int i = 1;
    int input_num = 0;  // num input values per command
    Command command;
    
    while (i < num) {
      // std::cout << cmd[i] << std::endl;
      if (cmd[i][0] == '-' || IsFile(cmd[i])) {
	// fresh command -command or _____.png
	if (i > 1) {  // push the previous command to the list
	  // std::cout << "Pushing to list\n";
	  command.num_args = input_num;
	  command_list_.push_back(command);
	}
	strcpy(command.name, cmd[i]);
	input_num = 0;
      } else if (IsFloat(cmd[i])) {
	// safe to convert to floating point value
	command.input[input_num] = strtof(cmd[i], NULL);
	input_num++;
      } else {
	std::cout << "Unexpected input: " << cmd[i] << std::endl;
      }
      i++;
    }
    // push the last Commands
    command.num_args = input_num;
    command_list_.push_back(command);
  }

  void CommandLineProcessor::PrintCommands() {
    while (!command_list_.empty()) {
      std::cout << command_list_.front().name << " ";
      for (int i = 0; i < command_list_.front().num_args; i++) {
	std::cout << command_list_.front().input[i] << " ";
      }
      command_list_.pop_front();
      std::cout << std::endl;
    }
  }
}  // namespace image_tools
