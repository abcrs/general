#include "command_line_processor.h"
#include <iostream>


  
int main(int argc, char* argv[]) {
  image_tools::CommandLineProcessor clp = image_tools::CommandLineProcessor(argc, argv);
  clp.PrintCommands();
  return 0;
}
