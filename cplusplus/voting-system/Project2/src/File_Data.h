#ifndef FILE_DATA_H_
#define FILE_DATA_H_

// Includes < >

// Includes " "
#include "Candidate_Data.h"
#include "Party_Data.h"
#include <utility>

/** \brief File_Data: Load data and perform data processing. */
class File_Data {
 public:
  /** \brief Prompt the user for a filename, load the file into File_Data format. */
  File_Data();

  /** \brief Load and initialize filename.csv into File_Data.
      \param filename a char * filename in .csv format.
  */
  File_Data(char * filename);

  /** \brief Set fields of File_Data without a file, for testing.
   */
 File_Data(char * t, int np, Party_Data * prty, int ns, int nb, int nc, Candidate_Data * cnds)
   : voting_type_(t), num_parties_(np), party_list_(prty), num_seats_(ns), num_ballots_(nb),
    num_candidates_(nc), candidates_(cnds)
  {}

  ~File_Data();

  /** \brief Load_File(filename): Load a .csv file into the File_Data format (OPL and CPL).
      \param filename a char * filename in .csv format.
   */
  void Load_File(char * filename);

  /** \brief return party_list_ */
  Party_Data * get_party_list_() { return party_list_; }

  /** \brief return voting_type_ */
  char * get_voting_type_() { return voting_type_; }

  /** \brief return num_parties_ */
  int get_num_parties_() { return num_parties_; }

  /** \brief return num_seats_ */
  int get_num_seats_() { return num_seats_; }

  /** \brief return num_ballots_ */
  int get_num_ballots_() { return num_ballots_; }

  /** \brief return num_candidates_ */
  int get_num_candidates_() { return num_candidates_; }

  /** \brief set quota */
  void set_quota_(){ quota_ = get_num_ballots_() / get_num_seats_(); }

  /** \brief return candidates_ */
  Candidate_Data * get_candidates_() { return candidates_; }

  /** \brief return quota_ */
  float get_quota_() { return quota_; }

  /** \brief return random seed */
  int get_seed_() { return rand_seed_; }



  /**
      Convert the File_Data from OPL to CPL format
      This will take the data from candidates_ and generate party_list_,
      and other fields (doesn't calculate Party_Data.seats_ field).
      Load_File must be run prior.

      OPL assumptions after Load_File:
      1. variables set: voting_type_, num_seats_, num_ballots_, num_candidates.
      2. candidates_ will be filled in with the following fields: name_, party_, votes_.
      Need to:
      1. generate: num_parties_, party_list_.
      2. store a local var to calculate num_candidates per party.
      3. Add candidates + their votes to their parties.
      4. Run Tie_Break_OPL to sort by votes and break ties.
      5. rank the candidates (that are sorted and tie broken) in increasing order.
*/
  void Convert_OPL_To_CPL();

  /** Using the party_list_ (with all fields generated except for the seats_ field)
      generate the seats_ field.
   */
  void Calculate_Num_Seats();

  /** \breif Free all memory in the FileData structure
   */
  void Free_Memory();

private:
  /** Load values without a file
      For testing only
  */
  void Test_File_Data();

  /** To be used in Convert_OPL_To_CPL
      This will take the Candidate_Data array and generate num_parties_
   */
  void Calculate_Num_Parties();

  /** To be used in Convert_OPL_To_CPL
      Generate the party_list_ field
      Will not generate the seat field
      Must be run after num_parties_ is calculated and party_list_ = null
      To be used in Convert_OPL_To_CPL after Calculate_Num_Parties
   */
  void Generate_Party_List();

  /** TODO
      To be used in Convert_OPL_To_CPL
      Generate_Party_List must have been called
      Rank_Party_Candidates will go to each party in the party_list_:
      1. Sort the Part_Data.candidates_ (decreasing order by votes_).
      2. Run Break_Tie_Candidate (to shuffle equal vote candidates).
      3. Assign ranks [1, Party_Data.num_candidates_] to the array
      return / fall out (ranks have been calculated)
   */
  void Rank_Party_Candidates();

  /** TODO
      Sort each Candidate_Data array (candidates_) in party_list_
      Decreasing order by Candidate_Data.votes_
      Using
  */
  void Sort_Candidates();

  /** \brief QuickSort for Sort_Candidates
      \param prty the current party that holds the candidate array to sort
      \param p left bound
      \param r right bound
   */
  void QuickSort_Cand(int prty, int p, int r);

  /** \brief QuickSort for Sort_Candidates
      \param prty the current party that holds the candidate array to sort
      \param p left bound
      \param r right bound
      \return new split value
   */
  int Partition_Cand(int prty, int p, int r);

  /** Philip Siedlecki  TODO
      Break_Tie will first sort the list
      Break_Tie will then scan through the list, keeping track of any tied elements,
      all elements within the tied region will be randomly scrambled
      by roll of an n sided die (n tied candidates).
      (works for multiple tied sections i.e. "A:5, B:5, C:5, D:4, E:4").
  */
  void Break_Tie_Candidates();

  /** \brief Randomize the positions of candidates in prty
      \param prty the current party that contains the candidate array
      \param l the left index into the candidate array
      \param r the right index into the candidate array

      Randomly shuffle the candidates (including l and r) in
      party_list_[prty].candidates_
   */
  void Randomize_Candidates(int prty, int l, int r);

  /** \brief Swap two candidates
      \param c1 a pointer to the first candidate
      \param c2 a pointer to the second candidate
   */
  void Swap_Candidates(Candidate_Data * c1, Candidate_Data * c2);

  /** To be used withing Generate_Party_List()
      This will set the num_candidates_, votes_, name_ field for each Party_Data[i]
   */
  void Calculate_Num_Candidates_Per_Party();

  /** Copy Candidates from candidates_ to their parties + allocate the
      Party_Data.candidates_ array.
   */
  void Copy_Candidates_To_Party();



  /**
      Break_Tie will first sort the list
      Break_Tie will then scan through the list, keeping track of any tied elements,
      all elements within the tied region will be randomly scrambled
      by roll of an n sided die (n tied candidates).
      (works for multiple tied sections i.e. "A:5, B:5, C:5, D:4, E:4").
  */
  void Break_Tie_Party();

  /** Helper functions used in Calculate_Num_Seats()
   */
  static int randomfunc(int j);

  /** Helper functions used in Calculate_Num_Seats()
   */
  static bool cmp(const std::pair<int,int> &p1,const std::pair<int,int> &p2);



  // Variables

  /** \brief OPL or CPL */
  char * voting_type_;

  /** \brief Number of parties in the race. */
  int num_parties_;

  /** \brief Party data array, must be in CPL format after constructor is called. */
  Party_Data * party_list_;

  /** \brief Total number of seats to be given for the current election. */
  int num_seats_;

  /** \brief The total number of ballots. */
  int num_ballots_;

  /** \brief The total number of candidates (any party). */
  int num_candidates_;

  /** \brief An array of candidates, used as an intermediate storage for OPL data
      (not needed once the OPL data is transformed into CPL data). */
  Candidate_Data * candidates_;

  /** \brief num_ballots_ / num_seats_ */
  float quota_;

  /** \brief random seed chosen to shuffle party_list_ */
  unsigned int rand_seed_;
};
#endif
