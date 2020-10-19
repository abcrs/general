#include "Voting_System.h"
#include "File_Data.h"
// #include "src/controller.h"
#include "src/GUI.h"

#include <stdio.h>
#include <fstream>
#include <iostream>

#include "src/GUI.h"

int main(int argc, char * argv[]) {
  Voting_System * v;
  char * filename;
  if (argc > 1) {
    filename = argv[1];
    v = new Voting_System(filename);
    v->get_file_data_();
    v->Media_File();
    v->Audit_File("test.txt");
    v->Display_Winners();
    delete v;
    return 0;
  }
  else {
    // v = new Voting_System();
    GUI gui(1280, 720);
    gui.Run();

  }
  /*
  v->get_file_data_();
  v->Media_File();
  v->Audit_File();
  v->Display_Winners();
  */

  // The controller creates both the arena and viewer
  /*
  auto *controller = new Controller(argc, argv);

  // The controller will call Run of the viewer
  controller->Run();
  */
  // delete v;

  return 0;
}
