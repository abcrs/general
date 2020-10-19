#ifndef CANDIDATE_DATA_H_
#define CANDIDATE_DATA_H_

// Includes < >
#include <stddef.h>
#include <string.h>
// Includes " "


/** \brief Candidate_Data is a public class to be used as a datatype to store
    data related to a Candidate. */
class Candidate_Data {
 public:
  /** \breif Default constructor */ 
  Candidate_Data() : name_(NULL), party_('-'), votes_(0), party_rank_(-1) {}

  /** \breif Constructor to be used for testing (set fields without file) */ 
  Candidate_Data(char * name, char p, int v, int r);
  
  /** \breif Copy Constructor */ 
  Candidate_Data(const Candidate_Data &C);

  Candidate_Data& operator=(const Candidate_Data &rhs);

  ~Candidate_Data() { delete [] name_; name_ = NULL; }
  // Need a constructor that creates new memory for a string lit.
  
  /** \brief name_: Candidate Name "John" */
  char * name_;
  
  /** \brief party_: Candidate Party 'R','D','I' */
  char party_;

  /** \brief votes_: Candidate Vote total */
  int votes_;

  /** \brief party_rank_: Candidate's Ranking within the party */
  int party_rank_;
};

#endif
