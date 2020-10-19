// <>
#include <string.h>
#include <iostream>

#include "Candidate_Data.h"

Candidate_Data::Candidate_Data(const Candidate_Data &C) {
  int l = strlen(C.name_) + 1;  // alloc len + 1 (end of line char)
  name_ = new char[l];
  strcpy(name_, C.name_);
  party_ = C.party_;
  votes_ = C.votes_;
  party_rank_ = C.party_rank_;
}

Candidate_Data::Candidate_Data(char * name, char p, int v, int r) {
  party_ = p;
  votes_ = v;
  party_rank_ = r;
  name_ = new char[strlen(name) + 1];
  strcpy(name_, name);
}

Candidate_Data& Candidate_Data::operator=(const Candidate_Data &rhs) {  // overload assignment operator
  if (this != &rhs) {               // do not copy to yourself
    int l = strlen(rhs.name_) + 1;  // alloc len + 1 (end of line char)
    name_ = new char[l];
    strcpy(name_, rhs.name_);
    party_ = rhs.party_;
    votes_ = rhs.votes_;
    party_rank_ = rhs.party_rank_;
  }
  return *this;                     // always end with this line
}
