#include <string.h>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdlib.h>     /* malloc, free, rand */
#include <iostream>
#include <sys/time.h>

#include <map>
#include <random>
#include <vector>
#include <algorithm>
#include <utility>

#include <ctime>

#include "File_Data.h"

/** \brief MAX_NUM_PARTY: Used in OPL to CPL conversion */
#define MAX_NUM_PARTY 1000  // Maximum number of parties

File_Data::File_Data() {
}

File_Data::File_Data(char * filename) {
  num_parties_ = 0;
  Load_File(filename);
  Convert_OPL_To_CPL();
  Calculate_Num_Seats();
}

File_Data::~File_Data() {
  delete [] this->candidates_;
  this->candidates_ = NULL;

  delete [] party_list_;
  party_list_ = NULL;


  delete [] voting_type_;
  voting_type_ = NULL;
}
/*
void File_Data::Free_Memory() {
  std::cout << "Deleting [" << num_parties_ << "] parties.\n";
  for (int i = 0; i < num_parties_; i++) {
    std::cout << "Party #" << i << " has #" << party_list_[i].num_candidates_ << " candidates \n";
    for (int j = 0; j < party_list_[i].num_candidates_; j++) {
      delete [] (party_list_[i].candidates_[j].name_);
    }
    delete [] party_list_[i].candidates_;
  }
  delete [] party_list_;
  delete [] candidates_;
  delete [] voting_type_;
}
*/
/*
void File_Data::Test_File_Data() {
  char * cand_names = new char[200];
  strcpy(&cand_names[0], "Phil");
  strcpy(&cand_names[10], "Al");
  strcpy(&cand_names[20], "Barry");
  strcpy(&cand_names[30], "Sally");
  strcpy(&cand_names[40], "Tom");
  strcpy(&cand_names[50], "Troy");
  candidates_ = new Candidate_Data[6];
  candidates_[0] = Candidate_Data(&cand_names[0] , 'R', 100, -1);
  candidates_[1] = Candidate_Data(&cand_names[10]   , 'R', 50 , -1);
  candidates_[2] = Candidate_Data(&cand_names[20], 'R', 20 , -1);
  candidates_[3] = Candidate_Data(&cand_names[30], 'D', 100, -1);
  candidates_[4] = Candidate_Data(&cand_names[40]  , 'D', 30 , -1);
  candidates_[5] = Candidate_Data(&cand_names[50] , 'I', 40 , -1);

  voting_type_ = (char *) malloc(sizeof(char) * 5);
  strcpy(voting_type_, "OPL");

  num_parties_ = -1;

  party_list_ = NULL;

  num_seats_ = 3;

  num_ballots_ = 340;

  num_candidates_ = 6;
}
*/

void File_Data::Load_File(char * filename) {
  FILE* file = fopen(filename, "r");
  party_list_ = NULL;
  candidates_ = NULL;
  voting_type_ = NULL;

  // if file cannot be opened, exit
  if (!file) {
    std::cerr << "Failed to open the file: " << filename << std::endl;
    exit(1);
  }

  // if file is not of CSV, exit and alert user to issue
  std::string fname(filename);
  if (fname.substr(fname.length()-4, fname.length()).compare(".csv") != 0) {
    std::cerr << "Failed to open the file: " << filename
	      << "; File is not of CSV format" << std::endl;
    exit(1);
  }

  // if line one is not either OPL or CPL, exit and alert user to issue
  char line[128];
  fgets(line, sizeof(line), file);
  strtok(line, "\n");
  if ((strcmp(line, "OPL") != 0) && (strcmp(line, "CPL") != 0)) {
    std::cerr << "Failed to open the file: " << filename
	      << "; File should be lead with either OPL or CPL" << std::endl;
    exit(1);
  }

  // Read the contents and store in either candidate data or party_data depending on
  // voting_type_
  if (strcmp(line, "OPL") == 0) {
    // voting_type_ = (char*) malloc(sizeof(line));
    voting_type_ = new char[strlen(line)+1];
    strcpy(voting_type_, line);
    fgets(line, sizeof(line), file);
    num_seats_ = atoi(line);
    fgets(line, sizeof(line), file);
    num_ballots_ = atoi(line);
    fgets(line, sizeof(line), file);
    num_candidates_ = atoi(line);

    // allocate candidates array, fill name and party feilds, init rank and vote feilds
    // candidates_ = (Candidate_Data*) malloc(sizeof(Candidate_Data)*num_candidates_);
    candidates_ = new Candidate_Data[num_candidates_];
    char* token;
    for (int i = 0; i < num_candidates_ ; i++) {
      fgets(line, sizeof(line), file);
      token = strtok(line, "[,]");
      // candidates_[i].name_ = (char*) malloc(sizeof(token));
      candidates_[i].name_ = new char[strlen(token)+1];
      strcpy(candidates_[i].name_, token);
      token = strtok(NULL, "[,]");
      candidates_[i].party_ = (char) token[0];
      candidates_[i].party_rank_ = -1;
      candidates_[i].votes_ = 0;
    }

    // count and increment votes for each candidate
    for (int i = 0 ; i < num_ballots_ ; i++) {
      fgets(line, sizeof(line), file);
      int cand_ident = 0;
      while (line[cand_ident] != '\0' && cand_ident < num_candidates_) {
        if (line[cand_ident] == '1') {
          candidates_[cand_ident].votes_++;
          break;
        }
        cand_ident++;
      }
    }
    // if voting_type_ is CPL
  } else {
    // voting_type_ = (char*) malloc(sizeof(line));
    voting_type_ = new char[strlen(line)+1];
    strcpy(voting_type_, line);
    fgets(line, sizeof(line), file);
    num_parties_ = atoi(line);

    // parse parties in order of ballot listing and set party name_ for each party_list_
    // init unknown Party_Data members to 0 values.
    char* token;
    fgets(line, sizeof(line), file);
    token = strtok(line, "[,]");
    // party_list_ = (Party_Data*) malloc(sizeof(Party_Data)*num_parties_);
    party_list_ = new Party_Data[num_parties_];
    for (int i = 0; i < num_parties_; i++) {
      party_list_[i].name_ = (char) token[0];
      party_list_[i].votes_ = 0;
      party_list_[i].seats_ = 0;
      party_list_[i].candidates_ = NULL;
      token = strtok(NULL, "[,]");
    }

    fgets(line, sizeof(line), file);
    num_seats_ = atoi(line);
    fgets(line, sizeof(line), file);
    num_ballots_ = atoi(line);
    fgets(line, sizeof(line), file);
    num_candidates_ = atoi(line);

    // when ever a candidate with a party ranking of 1 is encoutnered
    // increment party_ident. re-init num_cands_in_party to 0 when encounter
    // new candidate of 1 party rank
    // hold newly read candidate date in tmp_cand until information their party
    // info can is attained
    int party_ident = -1;
    int num_cands_in_party = -1;
    Candidate_Data * tmp_cand = new Candidate_Data();
    for (int i = 0; i < num_candidates_; i++) {
      fgets(line, sizeof(line), file);
      token = strtok(line, "[,]");
      tmp_cand->name_ = token;
      token = strtok(NULL, "[,]");
      tmp_cand->party_ = (char) token[0];
      token = strtok(NULL, "[,]");
      tmp_cand->party_rank_ = atoi(token);
      tmp_cand->votes_ = -1;

      // if see a candidate at rank 1, entered a new party, reset num_candidates_in_party
      // and increment party_ident
      if (tmp_cand->party_rank_ == 1) {
        num_cands_in_party = -1;
        party_ident++;
      }
      // if candidates for party is NULL, init Candidate_Data array to hold all candidates
      if(!party_list_[party_ident].candidates_) {
        // party_list_[party_ident].candidates_ =
        //   (Candidate_Data*) malloc(sizeof(Candidate_Data)*num_candidates_);
        party_list_[party_ident].candidates_ =
          new Candidate_Data[num_candidates_];
      }
      // knowing the candidate index relative to their party_list_ and party_rank_
        // fill candidate feilds for party_list_ and update num_candidates_ for party_list_
      num_cands_in_party++;
      party_list_[party_ident].num_candidates_ = num_cands_in_party+1;
      // party_list_[party_ident].candidates_[num_cands_in_party].name_ =
      //   (char*) malloc(sizeof(tmp_cand.name_));
      party_list_[party_ident].candidates_[num_cands_in_party].name_ =
        new char[strlen(tmp_cand->name_)+1];
      strcpy(party_list_[party_ident].candidates_[num_cands_in_party].name_,
        tmp_cand->name_);
      party_list_[party_ident].candidates_[num_cands_in_party].party_ =
        tmp_cand->party_;
      party_list_[party_ident].candidates_[num_cands_in_party].party_rank_ =
        tmp_cand->party_rank_;
      party_list_[party_ident].candidates_[num_cands_in_party].votes_ = -1;
    }
    // count and increment votes for each party
    for (int i = 0 ; i < num_ballots_ ; i++) {
      fgets(line, sizeof(line), file);
      party_ident = 0;
      while (line[party_ident] != '\0' && party_ident < num_parties_) {
        if (line[party_ident] == '1') {
          party_list_[party_ident].votes_++;
          break;
        }
        party_ident++;
      }
    }
  }

  fclose(file);
}

/* OPL assumptions after Load_File:
   1. variables set: voting_type_, num_seats_, num_ballots_, num_candidates.
   2. candidates_ will be filled in with the following fields: name_, party_, votes_.
   Need to:
   1. generate: num_parties_, party_list_.
   2. store a local var to calculate num_candidates per party.
   3. Add candidates + their votes to their parties.
   4. Run Tie_Break_OPL to sort by votes and break ties.
   5. rank the candidates (that are sorted and tie broken) in increasing order.

*/
void File_Data::Convert_OPL_To_CPL() {
  if (strcmp(voting_type_, "CPL") == 0) {  // check that the file needs to be converted
    return;
  }
  Calculate_Num_Parties();  // set num_parties_
  Generate_Party_List();    // set party_list_
  Rank_Party_Candidates();  // set candidates_.party_rank_

}

void File_Data::Calculate_Num_Parties() {
  num_parties_ = 0;
  bool party_visited = false;
  char * party_str = new char[MAX_NUM_PARTY];  // store the represented parties.

  // init party_str to non party symbol data.
  for (int i = 0; i < MAX_NUM_PARTY; i++) {
    party_str[i] = '-';
  }
  // Loop through candidates_ and set num_parties_
  for (int i = 0; i < num_candidates_; i++) {
    // Start at the last party added
    // search party_str to pos 0, if the party exists, set party_visited
    for (int j = num_parties_; j >= 0; j--) {
      if (party_str[j] == candidates_[i].party_) {  // party exists in party_str
	party_visited = true;
      }
    }  // All char in party_str have been visited, party_visited will be set.
    if (!party_visited) {  // party has not been visited, add it
      party_str[num_parties_] = candidates_[i].party_;
      num_parties_++;
    }
    party_visited = false;  // reset flag for next loop.
  }
  delete [] party_str;
}

void File_Data::Generate_Party_List() {
  // printf("Nnum parties (Gen Party List) %d\n", num_parties_);
  party_list_ = new Party_Data[num_parties_];
  // Allocate the memory for party_list
  /*
  for (int i = 0; i < num_parties_; i++) {
    party_list_[i] = Party_Data();
  }  // all memory set / alloced
  */
  Calculate_Num_Candidates_Per_Party();
  Copy_Candidates_To_Party();
}

void File_Data::Calculate_Num_Candidates_Per_Party() {
  int num_parties_added = 0;
  bool party_match = false;
  // for each candidate, increment their party num_cand by 1
  for (int i = 0; i < num_candidates_; i++) {
    // Search all parties (init to '-', for the current cand. party)
    for (int j = 0; j < num_parties_added; j++) {
      if (party_list_[j].name_ == candidates_[i].party_) {
	// Party match, break out of the for loop
	party_list_[j].num_candidates_++;
	party_list_[j].votes_ += candidates_[i].votes_;
	party_match = true;
	break;
      }
    }  // looped through all parties, has there been a match? (party_match is set)
    if (!party_match) {  // no match found, add the party and votes
      party_list_[num_parties_added].name_ = candidates_[i].party_;
      party_list_[num_parties_added].num_candidates_++;
      party_list_[num_parties_added].votes_ += candidates_[i].votes_;

      num_parties_added++;  // We have added a party
      if (num_parties_added > num_parties_) {  // check that we have not added too many
	printf("ERROR (Candidates_Per_Party): Added (%d), max (%d)\n", num_parties_added, num_parties_);
      }
    }
    party_match = false;  // reset party_match
  }

  // Debug code...
  /*for (int i = 0; i < num_parties_; i++) {
    // printf("Party: %c, Num cand: %d\n", party_list_[i].name_, party_list_[i].num_candidates_);
    }*/
}

void File_Data::Copy_Candidates_To_Party() {
  int num_cand_added;  // number of candidates added to the current party
  for (int i = 0; i < num_parties_; i++) {  // loop through each party, add all of its cands
    num_cand_added = 0;
    // printf("i: %d, Num_Candidates_ : %d\n", i, party_list_[i].num_candidates_);
    party_list_[i].candidates_ = new Candidate_Data[party_list_[i].num_candidates_];
    for (int j = 0; j < num_candidates_; j++) {  // check all candidates 'Party_' to add them to i
      if (party_list_[i].name_ == candidates_[j].party_) {
	if (num_cand_added > party_list_[i].num_candidates_) {
	  printf("ERROR (Copy_Candidates_To_Party) : Adding too many candidates\n");
	}
	// If candidate belongs to party(i), add them to num_cand_added in party_.cand array
	// party_list_[i].candidates_[num_cand_added] = Candidate_Data(candidates_[j]);
	party_list_[i].candidates_[num_cand_added] = candidates_[j];
	num_cand_added++;
      }
    }
  }

}

void File_Data::Rank_Party_Candidates() {
  Sort_Candidates();
  Break_Tie_Candidates();
  for (int i = 0; i < num_parties_; i++) {
    for (int j = 0; j < party_list_[i].num_candidates_; j++) {
      party_list_[i].candidates_[j].party_rank_ = j + 1;
    }
  }
}

void File_Data::Sort_Candidates() {
  // Sort the candidate arrays of each party
  for (int i = 0; i < num_parties_; i++) {
    QuickSort_Cand(i, 0, party_list_[i].num_candidates_ - 1);
  }
}

void File_Data::Break_Tie_Candidates() {
  int l, r, v;  // l: left, r: right, v:vote
  bool tie = false;
  for (int i = 0; i < num_parties_; i++) {  // search each party
    // Set indexes to 0, and votes to the first element or cand array
    v = party_list_[i].candidates_[0].votes_;
    l = 0;
    tie = false;
    // Look through each cand array for a tie
    for (int j = 1; j < party_list_[i].num_candidates_; j++) {
      r = j;
      if (party_list_[i].candidates_[r].votes_ == v) {
	tie = true;
      } else {  // end of tie section found
	if (tie) {
	  Randomize_Candidates(i, l, r - 1);
	}
	l = r;
	v = party_list_[i].candidates_[l].votes_;
	tie = false;
      }
    }
    if (tie) {  // end case, if the last elements are a tie
      Randomize_Candidates(i, l, party_list_[i].num_candidates_ - 1);
    }
  }
}

void File_Data::Randomize_Candidates(int prty, int l, int r) {
  // srand (time(NULL));
  struct timeval time;
  gettimeofday(&time, NULL);
  party_list_[prty].rand_seed_ = (time.tv_sec * 1000) + (time.tv_usec * 1000);
  srand(party_list_[prty].rand_seed_);
  // std::cout << "l: " << l << " r: " << r << std::endl;
  int num_to_swap = r - l + 1;
  int * index_array = (int *) malloc(sizeof(int) * num_to_swap);
  Candidate_Data * cand_copy = new Candidate_Data[num_to_swap];
  int r_index;  // random index
  // index_array contains indexes in the tie range of indexes
  // randomly assign them to candidates in this range
  // cand_copy contains the original order of candidates (so we don't overwrite any data)
  for (int i = 0; i < num_to_swap; i++) {
    index_array[i] = i + l;
    // cand_copy[i] = Candidate_Data(party_list_[prty].candidates_[l + i]);
    cand_copy[i] = party_list_[prty].candidates_[l + i];
  }
  // Assign candidate(l + i) to a random possition in the index_array
  for (int i = 0; i < num_to_swap; i++) {
    r_index = rand() % (num_to_swap - i);
    // std::cout << "Swapping: " << party_list_[prty].candidates_[index_array[r_index]].name_
    // << " > " << cand_copy[i].name_ << std::endl;
    Swap_Candidates(&(party_list_[prty].candidates_[index_array[r_index]]), &(cand_copy[i]));
    // move the last item to replace the used random index
    index_array[r_index] = index_array[num_to_swap - i - 1];
  }

  delete [] cand_copy;
  free(index_array);
}

void File_Data::QuickSort_Cand(int prty, int p, int r) {
  // Code from Intro. to Algs. Third Edition

  int q;
  if (p < r) {
    // printf("QuickSort_Cand: prty: %d, p: %d, r: %d\n", prty, p, r);
    q = Partition_Cand(prty, p, r);
    QuickSort_Cand(prty, p, q - 1);
    QuickSort_Cand(prty, q + 1, r);
  }
}

int File_Data::Partition_Cand(int prty, int p, int r) {
  // Code from Intro. to Algs. Third Edition
  // printf("Partition_Cand: prty: %d, p: %d, r: %d\n", prty, p, r);
  int x = party_list_[prty].candidates_[r].votes_;
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (party_list_[prty].candidates_[j].votes_ > x) {
      i++;
      Swap_Candidates(&party_list_[prty].candidates_[i],
		      &party_list_[prty].candidates_[j]);
    }
  }
  Swap_Candidates(&party_list_[prty].candidates_[i + 1],
		  &party_list_[prty].candidates_[r]);
  return i + 1;
}

void File_Data::Swap_Candidates(Candidate_Data * c1, Candidate_Data * c2) {
  char * temp_name;
  char temp_party;
  int temp_votes;
  int temp_party_rank;

  temp_name = c1->name_;
  temp_party = c1->party_;
  temp_votes = c1->votes_;
  temp_party_rank = c1->party_rank_;

  c1->name_ = c2->name_;
  c1->party_ = c2->party_;
  c1->votes_ = c2->votes_;
  c1->party_rank_ = c2->party_rank_;

  c2->name_  = temp_name;
  c2->party_ = temp_party;
  c2->votes_ = temp_votes;
  c2->party_rank_ = temp_party_rank;

}



// A helper function for Calculate_Num_Seats()
bool File_Data::cmp(const  std::pair<int,int> &p1,const  std::pair<int,int> &p2)
{
  return p1.second<p2.second;
}

// A helper function for Calculate_Num_Seats()
int File_Data::randomfunc(int j)
{
  return rand() % j;
}

void File_Data::Calculate_Num_Seats() {
  // Set up the quota
  set_quota_();

  int party_num = get_num_parties_();
  float quota = get_quota_();
  int seat_sum = 0;

  // Variables to determine which party gets seats
  bool meet_quota = true;
  bool is_tie = false;
  int party_votes [party_num] = { };
  int tie_votes [party_num] = { };
  int tie_count = 0;
  int tie_break = -1;
  int max_votes = 0;
  int party_max = -1;

  // Fill a holder array with each party's votes
  for (int i = 0; i < party_num; i++) {
      party_votes[i] = party_list_[i].votes_;
  }

  // Repeat this loop until no parties have more votes than the quota
  // Each repetition will either end the loop or reduce one party's vote total
  // in the party_votes array, until all parties have less than the quota
  while (meet_quota) {
    // Re-initialize the values
    meet_quota = false;
    is_tie = false;
    tie_count = 0;
    tie_break = -1;
    max_votes = 0;
    party_max = -1;

    // If all the seats have been filled, do not attempt to find the next one
    // meet_quota set to false, so loop will end automatically if all seats are filled
    if (seat_sum < get_num_seats_()) {

      // Test each party to see which, if any, have enough votes to meet the quota
      for (int i = 0; i < party_num; i++) {
        if (party_votes[i] >= quota) {
          // The party with the most votes is awarded a seat first
          if (party_votes[i] > max_votes) {
            meet_quota = true;
            max_votes = party_list_[i].votes_;
            party_max = i;
            tie_votes[0] = i;
          }
          // If there is a tie between parties, start filling the tie_votes array
          else if (party_votes[i] == max_votes) {
            tie_count += 1;
            tie_votes[tie_count] = i;
            is_tie = true;
          }
        }
      }
    }

    // If there is a tie, use a tiebreaker to determine which party is
    // awarded a seat in this iteration
    if (is_tie) {
      std::srand(std::time(0));
      tie_count += 1;
      tie_break = rand() % tie_count;
      party_max = tie_votes[tie_break];
    }

    // If one party has met the quota, reduce that party's vote total
    // If that party has more candidates who can receive seats, award one
    if (meet_quota) {
      party_votes[party_max] -= (int)quota;
      if (party_list_[party_max].seats_ < party_list_[party_max].num_candidates_) {
        party_list_[party_max].seats_ += 1;
        seat_sum += 1;
      }
    }
  }

  // A map to store the remainders
  std::map<int,int> remainders;

  for (int i = 0; i < party_num; i++) {
    if (party_list_[i].seats_ < party_list_[i].num_candidates_) {
      remainders[i] = party_list_[i].votes_ % (int)quota;
    }
  }
  std::vector<std::pair<int,int> > arr;
  for (std::map<int,int>::iterator it=remainders.begin();it!=remainders.end();++it) {
    arr.push_back(std::make_pair(it->first,it->second));
  }
  // Sort by value in an increading order
  sort(arr.begin(),arr.end(),cmp);

  // When there are more seats to be allocated
  while (seat_sum < get_num_seats_()) {

    std::vector<std::pair<int,int> >::iterator it1 = prev(arr.end(),1);
    std::vector<std::pair<int,int> >::iterator it2 = prev(arr.end(),2);
    // Don't have ties
    if (it1->second!=it2->second) {

      // Process seat accordingly, use the last(biggest）number
      party_list_[it1->first].seats_ += 1;
      seat_sum +=1;
      arr.erase(it1);
    }
    // Have ties
    else {
    std::vector<std::pair<int,int> >::iterator it3;
    for (it3=prev(arr.end(),1);it3->second == prev(arr.end(),1)->second;--it3) {}

    // it3 points to the inital element of same number
    it3++;
    std::srand(std::time(0));
    // Randomely shuffle the elements with the same value
    random_shuffle(it3, arr.end(),randomfunc);

    // Process seat accordingly, use the last(biggest）number
    party_list_[it1->first].seats_ += 1;
    seat_sum +=1;
    arr.erase(it1);
  }
}
}
