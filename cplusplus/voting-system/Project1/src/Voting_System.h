#ifndef VOTING_SYSTEM_H_
#define VOTING_SYSTEM_H_

#include "File_Data.h"
#include <fstream>


/** @brief Voting_System: Create File_Data object, create Audit and Meida files, Display Winners. */
class Voting_System {
 public:
  /** \brief Create File_Data object with no filename. */
  Voting_System();

  /** \brief Create File_Data object with filename.
      \param filename a char * filename in .csv format.
  */
  Voting_System(char * filename);

  // A constructor for testing
  Voting_System(int a);

  /** \brief Create a Voting_System object with a processed file
      \param A File_Data object that has already been processed */
  Voting_System(File_Data * filedata);

  ~Voting_System() { delete data_; data_ = NULL; }

  /** \brief Produce output file containing necessary audit information. */
  void Audit_File();

  /** \brief Produce output file containing results to be read by the media. */
  void Media_File();

  /** \brief Display winners on console for Voting Officials. */
  void Display_Winners();

  /** \brief Free all memory from file_Data */
  void V_Free_Memory();

 private:
  //Variables

  /** \brief Object containing all important data from election file. */
  File_Data * data_;

  /** \brief Establish name of file to be output
      \param The object of the output file and a bool to determine which kind of file */
  void Name_File(std::ofstream& out, bool isAudit);

  /** \brief Print to file all important information for recreating election.
      \param Output file where the information will be stored. */
  void Audit_Info(std::ofstream& out);

  /** \brief Print to file relevant information from the election for the media.
      \param Output file where the information will be stored, bool that determines if file is an audit. */
  void Gen_Info(std::ofstream& out, bool isAudit);
};
#endif
