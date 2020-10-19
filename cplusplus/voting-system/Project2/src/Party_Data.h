#ifndef PARTY_DATA_H_
#define PARTY_DATA_H_

// Includes < >

// Includes " "
#include "Candidate_Data.h"

/** \brief Party_Data is a data type meant to store all relevant information for each party. */
class Party_Data {
 public:
 Party_Data() : name_('-'), votes_(0), seats_(0), candidates_(NULL), num_candidates_(0), rand_seed_(0) {}

  /** \breif Constructor to be used for testing (set fields without file) */ 
  Party_Data(char name, int v, int s, int nc, Candidate_Data * cands) :
  name_(name), votes_(v), seats_(s), candidates_(cands) , num_candidates_(nc) {}

  /** \brief Copy constructor (Allocates new memory for name) */
  Party_Data(const Party_Data &p) {
    name_ = p.name_;
    votes_ = p.votes_;
    seats_ = p.seats_;
    candidates_ = p.candidates_;
    num_candidates_ = p.num_candidates_;
    rand_seed_ = p.rand_seed_;
  }

  ~Party_Data() {
    delete [] this->candidates_;
    this->candidates_ = NULL;
  }
  
  /** \brief name_: The name of the party. */
  char name_;
  
  /** \brief votes_: The total number of votes for the party. */
  int votes_;
  
  /** \brief seats_: The total number of seats won by the party. */
  int seats_;
  
  /** \brief  candidates_: The individuals that make up the party.*/
  Candidate_Data * candidates_;
  
  /** \brief  num_candidates_: The total number of candidates in the party.*/
  int num_candidates_;

  /** \brief random seed chosen to shuffle candidates_ (OPL only) */
  unsigned int rand_seed_;
};

#endif
