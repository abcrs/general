#ifndef MIA_COMMAND_LINE_PROCESSOR_H_
#define MIA_COMMAND_LINE_PROCESSOR_H_

// Author: Philip Siedlecki, University of Minnesota
// Copyright 2018

#include <image_editor.h>
#include <stdio.h>
#include <string.h>

#include <list>

#include "mia/image_editor_commands.h"

// 2097152 argc size

const int MAX_INPUT = 3;  // the maximum number of input args to a function
const int FILENAME_LEN = 255;

namespace image_tools {

  /** @brief This class is designed to Error check and run Mia commands from a terminal input. */
class CommandLineProcessor {
 public:
  CommandLineProcessor() {}

  /** @brief This should handle all calls, creating a list of commands to
      run */
  void ProcessCommandLine(int num, char **cmd);

  /** @brief Print off all command in the command_list_. */
  void PrintCommands();

  /** @brief Check all commands in the list for any invalid calls
      return true if all commands are valid, false if not. */
  bool CheckCommands();

  /** @brief Execute all commands in the command_list_
      CheckCommands SHOULD HAVE run validating the list.
      This ASSUMES ALL commands are VALID */
  void ExecuteCommands();

  /** @brief find file extensions in the input string
      return true if the extrensions are present
      will only return true if .png is present
      ".png" is currently valid, but will fail an existence check */
  bool IsFile(const char *buf);

  /** @brief return true if buff contains only digits and '.' values
      Will not work with negative values as '-' denotes a command
      there is no need to extend this to negative values as all filters / tools
      take (val >= 0). */
  bool IsFloat(const char *buf);

  /** @brief return true if the file exists, false if not
      checks the current directory for the file. */
  bool FileExists(const char * filename);

  /** @brief Print Command line help to stdout
      This will be printed when -h is called, edit the help menu here. */
  void PrintHelp();

  /** @brief Extract each command and place into a struct list */
  void ExtractCommands(int num, char ** cmd); 

 private:
  // This is for all commands, each command will have a name
  // and following arguments
  struct Command {
    char name[255];   // 255 char is max filename length
    float input[MAX_INPUT];
    int num_args;
  };

  std::list<Command> command_list_;  // list of all commands in order
};

}  // namespace image_tools

#endif  // MIA_COMMAND_LINE_PROCESSOR_H_
