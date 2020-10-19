#include <stdio.h>
#include <ctime>
#include <time.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "Voting_System.h"

Voting_System::Voting_System() {
  // Prompt user for filename if none is passed in
  // Create File_Data object with provided filename
  char * filename = new char[100];
  char inp[100];
  std::cout << "Please enter the name of the election file: ";
  // Get filename from user
  std::cin >> inp;
  strcpy(&filename[0],inp);
  data_ = new File_Data(filename);
  // Convert data in object to CPL style if in OPL style
  /*
  if (strcmp(data_->get_voting_type_(),"OPL") == 0) {
    data_->Convert_OPL_To_CPL();
  }
  // Calculate number of seats each party is awarded
  data_->Calculate_Num_Seats();
  */
  delete [] filename;
}

Voting_System::Voting_System(char * filename) {
  // Create File_Data object with filename
  data_ = new File_Data(filename);
  // Convert data in object to CPL style if in OPL style
  /*
  if (strcmp(data_->get_voting_type_(),"OPL") == 0) {
    data_->Convert_OPL_To_CPL();
  }
  // Calculate number of seats each party is awarded
  data_->Calculate_Num_Seats();
  */
}

/*void Voting_System::V_Free_Memory() {
  data_->Free_Memory();
  delete data_;
  }
*/

Voting_System::Voting_System(File_Data * filedata) {
  data_ = new File_Data(filedata[0]);
  // Convert data in object to CPL style if in OPL style
  /*
  if (strcmp(data_->get_voting_type_(),"OPL") == 0) {
    data_->Convert_OPL_To_CPL();
  }
  // Calculate number of seats each party is awarded
  data_->Calculate_Num_Seats();
  */
}

void Voting_System::Name_File(std::ofstream& out, bool isAudit) {
  // Use current time and date to create unique ID file
  // Format of file: Media_File-YYYY-MM-DD-HH:MM:SS
  time_t t = time(0);
  struct tm * now = localtime(&t);
  char buffer [31];
  // Determine name of file by voting type
  if (isAudit) {
    // Create file with time-related format
    strftime(buffer,31,"Audit_File-%F-%T.txt",now);
    out.open(buffer);
    // File header
    out << buffer << " Election Details" << std::endl << std::endl;
  }
  else {
    // Create file with time-related format
    strftime(buffer,31,"Media_File-%F-%T",now);
    out.open(buffer);
    // File header
    out << buffer << " Election Details" << std::endl << std::endl;
  }
}

void Voting_System::Audit_File() {
  // Output file with pertinent information for the media
  std::ofstream audit_out;
  // Name_File creates file with appropriate name
  // true indicates Audit File
  Name_File(audit_out, true);
  // Call info function with output file as parameter
  Audit_Info(audit_out);

  audit_out.close();
}

void Voting_System::Audit_File(std::string audit_name) {
  // Output file with pertinent information for the media
  std::ofstream audit_out;
  time_t t = time(0);
  struct tm * now = localtime(&t);
  char buffer [31];
  // Create file with time-related format
  strftime(buffer,31,"Audit_File-%F-%T.txt",now);
  audit_out.open(audit_name + ".txt");
  // File header
  audit_out << buffer << " Election Details" << std::endl << std::endl;

  // Call info function with output file as parameter
  Audit_Info(audit_out);

  audit_out.close();
}

void Voting_System::Audit_Info(std::ofstream& out) {
  // Add relevant information from File_Data that allows election to be rerun by hand
  out << "Type of Election: " << data_->get_voting_type_() << std::endl;
  out << "Number of Parties in Election: " << data_->get_num_parties_() << std::endl;
  out << "Number of Seats Available: " << data_->get_num_seats_() << std::endl;
  out << "Number of Ballots Submitted: " << data_->get_num_ballots_() << std::endl;
  out << "Number of Candidates in Election: " << data_->get_num_candidates_() << std::endl;
  out << "Number of votes required to win a seat before remainder: " << data_->get_quota_() << std::endl;
  out << std::endl;

  // Call general info function to print more election data
  // true indicates this is an Audit file
  Gen_Info(out, true);
}

void Voting_System::Media_File() {
  // Output file with pertinent information for the media
  std::ofstream media_out;
  // Call Name_File to create and open appropriately named file
  // false indicates not an Audit file
  Name_File(media_out, false);
  // Call print function with output file as parameter
  // false indicates not an Audit file
  Gen_Info(media_out, false);

  media_out.close();
}

void Voting_System::Gen_Info(std::ofstream& out, bool isAudit) {
  // Maximum candidate name length for formatting
  int max_name = 0;
  // Create a copy of the party_list_ to access the party information
  Party_Data * p_data = data_->get_party_list_();
  // When isOPL is true, the individual votes of a candidate are produced
  bool isOPL = false;
  if (strcmp(data_->get_voting_type_(),"OPL") == 0) {
    isOPL = true;
  }
  // Iterate through party_data_ to output each party
  for (int p = 0; p < data_->get_num_parties_(); p++) {
    max_name = 0;
    // Search through candidates in a party to find one with longest name
    // Save that value in max_name, reset for each new party
    for (int j = 0; j < p_data[p].num_candidates_; j++) {
      if ((int)strlen(p_data[p].candidates_[j].name_) > max_name) {
        max_name = strlen(p_data[p].candidates_[j].name_);
      }
    }
    // Begin outputting party data
    out << "\tParty Icon:\t\t" << p_data[p].name_ << std::endl
        << "\tParty Votes:\t" << p_data[p].votes_ << std::endl
        << "\tSeats Won:\t\t" << p_data[p].seats_ << std::endl;
    if (isAudit) {
      out << "Random Seed used for ties: " << p_data[p].rand_seed_ << std::endl;
    }
    // In order, print candidates contained in the party_data
    for (int i = 0; i < p_data[p].num_candidates_; i++) {
      out << "Rank: " << i+1 << "\t|| Candidate: ";
      out.width(max_name+3);
      // Output candidate name, with appropriate formatting
      out << p_data[p].candidates_[i].name_;
      // Output number of votes candidate received in CPL election
      if (isOPL) {
        out << "\t|| Votes: " << p_data[p].candidates_[i].votes_;
      }
      // If a candidate has won a seat, add Winner tag
      if (i < p_data[p].seats_) {
        out << "\t|| Winner!";
      }
      out << std::endl;
     }
     out << std::endl << std::endl;
   }
}

void Voting_System::Display_Winners() {
  // p_data copies the party list to access the parties
  Party_Data * p_data = data_->get_party_list_();
  // count is a helper for printing the winners
  int count;
  // Iterate through the parties, printing results from each
  for (int p = 0; p < data_->get_num_parties_(); p++) {
    // Set count to 0 for each new party.
    count = 0;
    // Print party and how many seat(s) it won
    if (p_data[p].seats_ > 0) {
      std::cout << p_data[p].name_ << " won " << p_data[p].seats_ << " seat(s).\n";
      std::cout << "The winner(s) from " << p_data[p].name_ << " are: " << std::endl;
      // Print each winner from the party. Increment count to stop loop
      while (count < p_data[p].seats_) {
        std::cout << "\t" << p_data[p].candidates_[count].name_ << std::endl;
        count++;
      }
    }
    // Alert voting official if a party won no seats.
    else {
      std::cout << p_data[p].name_ << " did not win any seats.\n";
    }
    std::cout << "\n";
  }
}

File_Data * Voting_System::get_file_data_() {
  return data_;
}
