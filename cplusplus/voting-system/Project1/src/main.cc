#include "Voting_System.h"
#include "File_Data.h"
#include <stdio.h>
#include <fstream>

int main(int argc, char * argv[]) {
  Voting_System * v;
  char * filename;
  if (argc > 1) {
    filename = argv[1];
    v = new Voting_System(filename);
  }
  else {
    v = new Voting_System();
  }
  v->Media_File();
  v->Audit_File();
  v->Display_Winners();

  delete v;

  return 0;
}
