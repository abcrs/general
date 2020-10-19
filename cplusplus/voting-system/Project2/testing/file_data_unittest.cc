#include "gtest/gtest.h"
#include <iostream>
#include "../src/File_Data.h"

class FileDataTest : public ::testing::Test {
  void SetUp () override {
    f0_type = new char[10];
    strcpy(f0_type, "");
    
    f1_type = new char[10];
    strcpy(f1_type, "OPL");
    
    f2_type = new char[10];
    strcpy(f2_type, "OPL");
    
    blank_cand_data = NULL; // new Candidate_Data();
    blank_party_data = NULL; //  new Party_Data();
    blank_file_data = new File_Data(f0_type, 0, blank_party_data, 0, 0, 0, blank_cand_data);
    
    cnds = new Candidate_Data[6];
    cnds[0] = Candidate_Data("Al", 'R', 50 , -1);
    cnds[1] = Candidate_Data("Phil" , 'R', 100,    -1);
    cnds[2] = Candidate_Data("Barry", 'R', 20 ,    -1);
    cnds[3] = Candidate_Data("Sally", 'D', 100,    -1);
    cnds[4] = Candidate_Data("Tom"  , 'D', 30 ,  -1);
    cnds[5] = Candidate_Data("Troy" , 'I', 40 ,   -1);

    f1 = new File_Data(f1_type, -1, NULL, 3, 340, 6, cnds);

    f1->Convert_OPL_To_CPL();
    prty = f1->get_party_list_();

    cnds2 = new Candidate_Data[4];
    cnds2[0] = Candidate_Data("A", 'R', 100, -1);
    cnds2[1] = Candidate_Data("B", 'R', 100, -1);
    cnds2[2] = Candidate_Data("C", 'R', 100, -1);
    cnds2[3] = Candidate_Data("D", 'R', 100, -1);

    f2 = new File_Data(f2_type, -1, NULL, 2, 400, 4, cnds2);

    f2->Convert_OPL_To_CPL();
    prty2 = f2->get_party_list_();
    }
  void TearDown () override {
    // delete blank_cand_data;
    // delete blank_party_data;
    delete blank_file_data;
    delete f1;
    delete f2;
  }

protected:
  
  Candidate_Data * blank_cand_data;
  Party_Data * blank_party_data;
  File_Data * blank_file_data;
  char* non_file_type = "test_files/fake_file.csv\0";
  char* bad_type = "test_files/test_bad_type.txt\0";
  char* wrong_format = "test_files/test_wrong_format.csv\0";
  char* good_opl = "test_files/test_good_OPL.csv\0";
  char* good_cpl = "test_files/test_good_CPL.csv\0";
  char* big_opl = "test_files/test_big_OPL.csv\0";
  char* big_cpl = "test_files/test_big_CPL.csv\0";
  char* good_opl_two = "test_files/test_good_OPL_2.csv\0";
  char* good_cpl_one = "test_files/test_good_CPL_1.csv\0";

  Candidate_Data * cnds;
  Party_Data * prty;
  Candidate_Data * cnds2;
  Party_Data * prty2;
  File_Data * f1;
  File_Data * f2;
  //Voting_System v;
  char * f0_type;
  char * f1_type;
  char * f2_type;
  

  // parties
  Party_Data * rep;
  Party_Data * dem;
  Party_Data * ind;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FileDataTest, LoadFileErrorTests) {
    // test non-existent file output
    // std::cerr << "Begin non-file test" << std::endl;
    ASSERT_DEATH(blank_file_data->Load_File(non_file_type), 
        "Failed to open the file: test_files/fake_file.csv\n");


    // test bad file type output
    // std::cerr << "Begin incorrect file type test" << std::endl;
    ASSERT_DEATH(blank_file_data->Load_File(bad_type), 
        "Failed to open the file: test_files/test_bad_type.txt; File is not of CSV format\n");



    // test wrong file format output
    // std::cerr << "Begin incorrectly formated file test" << std::endl;
    ASSERT_DEATH(blank_file_data->Load_File(wrong_format), 
        "Failed to open the file: test_files/test_wrong_format.csv; File should be lead with either OPL or CPL\n");


    // test large OPL file for running without exception
    // std::cerr << "Begin large OPL file execution test" << std::endl;
    ASSERT_NO_THROW(blank_file_data->Load_File(big_opl));

    
    
    // test large CPL file for running without exception
    // std::cerr << "Begin large CPL file execution test" << std::endl;
    ASSERT_NO_THROW(blank_file_data->Load_File(big_cpl));
}

TEST_F(FileDataTest, LoadFileOPLTest) {
  // test correct formating OPL load into file_data
  // std::cerr << "Begin OPL file load test" << std::endl;
  ASSERT_NO_THROW(blank_file_data->Load_File(good_opl));
  int num_seats = blank_file_data->get_num_seats_();
  int num_ballots = blank_file_data->get_num_ballots_();
  int num_cands = blank_file_data->get_num_candidates_();
  Candidate_Data * candidates = blank_file_data->get_candidates_();
  
  int expect_num_seats = 3;
  int expect_num_ballots = 9;
  int expect_num_cands = 6;
  Candidate_Data expect_candidates[6];
  expect_candidates[0] = Candidate_Data("Pike", 'D', 3, -1);
  expect_candidates[1] = Candidate_Data("Foster", 'D', 2, -1);
  expect_candidates[2] = Candidate_Data("Deutsch", 'R', 0, -1);
  expect_candidates[3] = Candidate_Data("Borg", 'R', 2, -1);
  expect_candidates[4] = Candidate_Data("Jones", 'R', 1, -1);
  expect_candidates[5] = Candidate_Data("Smith", 'I', 1, -1);
  
  EXPECT_EQ(num_seats, expect_num_seats);
  EXPECT_EQ(num_ballots, expect_num_ballots);
  EXPECT_EQ(num_cands, expect_num_cands);
  for (int i = 0 ; i < expect_num_cands ; i++) {
    EXPECT_STREQ(candidates[i].name_, expect_candidates[i].name_);
    EXPECT_EQ(candidates[i].party_, expect_candidates[i].party_);
    EXPECT_EQ(candidates[i].votes_, expect_candidates[i].votes_);
    EXPECT_EQ(candidates[i].party_rank_, expect_candidates[i].party_rank_);
  }
}

TEST_F(FileDataTest, LoadFileCPLTest) {
    // test correct formating CPL load into file_data
    // std::cerr << "Begin CPL file load test" << std::endl;
    ASSERT_NO_THROW(blank_file_data->Load_File(good_cpl));
    int num_parties = blank_file_data->get_num_parties_();
    int num_seats = blank_file_data->get_num_seats_();
    int num_ballots = blank_file_data->get_num_ballots_();
    int num_cands = blank_file_data->get_num_candidates_();
    Party_Data * parties = blank_file_data->get_party_list_();

    int expect_num_parties = 4;
    int expect_num_seats = 7;
    int expect_num_ballots = 13;
    int expect_num_cands = 10;
    Candidate_Data * expect_candidatesD = new Candidate_Data[3];
    expect_candidatesD[0] = Candidate_Data("Pike", 'D', -1, 1);
    expect_candidatesD[1] = Candidate_Data("Foster", 'D', -1, 2);
    expect_candidatesD[2] = Candidate_Data("Floyd", 'D', -1, 3);
    Candidate_Data * expect_candidatesR = new Candidate_Data[3];
    expect_candidatesR[0] = Candidate_Data("Deutsch", 'R', -1, 1);
    expect_candidatesR[1] = Candidate_Data("Wong", 'R', -1, 2);
    expect_candidatesR[2] = Candidate_Data("Walters", 'R', -1, 3);
    Candidate_Data * expect_candidatesG = new Candidate_Data[3];
    expect_candidatesG[0] = Candidate_Data("Jones", 'G', -1, 1);
    expect_candidatesG[1] = Candidate_Data("Smith", 'G', -1, 2);
    expect_candidatesG[2] = Candidate_Data("Lewis", 'G', -1, 3);
    Candidate_Data * expect_candidatesI = new Candidate_Data[1];
    expect_candidatesI[0] = Candidate_Data("Perez", 'I', -1, 1);
    
    Party_Data * expect_parties = new Party_Data[4];
    //expect_parties[0] = Party_Data('D', 3, 7, 3, expect_candidatesD);
    //expect_parties[1] = Party_Data('R', 5, 7, 3, expect_candidatesR);
    //expect_parties[2] = Party_Data('G', 4, 7, 3, expect_candidatesG);
    //expect_parties[3] = Party_Data('I', 1, 7, 1, expect_candidatesI);
    expect_parties[0] = Party_Data('D', 3, 7, 3, NULL);
    expect_parties[1] = Party_Data('R', 5, 7, 3, NULL);
    expect_parties[2] = Party_Data('G', 4, 7, 3, NULL);
    expect_parties[3] = Party_Data('I', 1, 7, 1, NULL);

    expect_parties[0].candidates_ = expect_candidatesD;
    expect_parties[1].candidates_ = expect_candidatesR;
    expect_parties[2].candidates_ = expect_candidatesG;
    expect_parties[3].candidates_ = expect_candidatesI;
    
    
    
    EXPECT_EQ(num_parties, expect_num_parties);
    EXPECT_EQ(num_seats, expect_num_seats);
    EXPECT_EQ(num_ballots, expect_num_ballots);
    EXPECT_EQ(num_cands, expect_num_cands);
    for (int i = 0 ; i < expect_num_parties ; i++) {
        EXPECT_EQ(parties[i].name_, expect_parties[i].name_);
        EXPECT_EQ(parties[i].num_candidates_, expect_parties[i].num_candidates_);
        EXPECT_EQ(parties[i].votes_, expect_parties[i].votes_);
        for (int k = 0 ; k < expect_parties[i].num_candidates_ ; k++) {
            EXPECT_STREQ(parties[i].candidates_[k].name_, 
                expect_parties[i].candidates_[k].name_);
            EXPECT_EQ(parties[i].candidates_[k].party_, 
                expect_parties[i].candidates_[k].party_);
            EXPECT_EQ(parties[i].candidates_[k].votes_, 
                expect_parties[i].candidates_[k].votes_);
            EXPECT_EQ(parties[i].candidates_[k].party_rank_, 
                expect_parties[i].candidates_[k].party_rank_);
        }
    }
}

TEST_F(FileDataTest, Cal_Num_No_Tie_OPL_Test) {
    // test correct formating OPL load into file_data
    // std::cerr << "Begin CPL file load test" << std::endl;
    ASSERT_NO_THROW(blank_file_data->Load_File(good_opl));
    int num_parties = blank_file_data->get_num_parties_();
    int num_seats = blank_file_data->get_num_seats_();
    int num_ballots = blank_file_data->get_num_ballots_();
    int num_cands = blank_file_data->get_num_candidates_();
    ASSERT_NO_THROW(blank_file_data->Convert_OPL_To_CPL());
    ASSERT_NO_THROW(blank_file_data->Calculate_Num_Seats());
    float quota = blank_file_data->get_quota_();

    Party_Data * parties = blank_file_data->get_party_list_();

    int expect_num_seats = 3;
    int expect_num_ballots = 9;
    int expect_num_cands = 6;
    float expect_quota = 3;
    int expect_seat_D = 2;
    int expect_seat_R = 1;
    int expect_seat_I = 0;

    EXPECT_EQ(num_seats, expect_num_seats);
    EXPECT_EQ(num_ballots, expect_num_ballots);
    EXPECT_EQ(quota, expect_quota);
    EXPECT_EQ(parties[0].seats_,expect_seat_D);
    EXPECT_EQ(parties[1].seats_,expect_seat_R);
    EXPECT_EQ(parties[2].seats_,expect_seat_I);
}

TEST_F(FileDataTest, Cal_Num_No_Tie_OPL_Two_Test) {
    // test correct formating OPL load into file_data
    // std::cerr << "Begin CPL file load test" << std::endl;
    ASSERT_NO_THROW(blank_file_data->Load_File(good_opl_two));
    int num_parties = blank_file_data->get_num_parties_();
    int num_seats = blank_file_data->get_num_seats_();
    int num_ballots = blank_file_data->get_num_ballots_();
    int num_cands = blank_file_data->get_num_candidates_();
    ASSERT_NO_THROW(blank_file_data->Convert_OPL_To_CPL());
    ASSERT_NO_THROW(blank_file_data->Calculate_Num_Seats());
    float quota = blank_file_data->get_quota_();

    Party_Data * parties = blank_file_data->get_party_list_();

    int expect_num_seats = 3;
    int expect_num_ballots = 9;
    int expect_num_cands = 6;
    float expect_quota = 3;
    int expect_seat_D = 1;
    int expect_seat_R = 1;
    int expect_seat_I = 1;

    EXPECT_EQ(num_seats, expect_num_seats);
    EXPECT_EQ(num_ballots, expect_num_ballots);
    EXPECT_EQ(quota, expect_quota);
    EXPECT_EQ(parties[0].seats_,expect_seat_D);
    EXPECT_EQ(parties[1].seats_,expect_seat_R);
    EXPECT_EQ(parties[2].seats_,expect_seat_I);
}

TEST_F(FileDataTest, Cal_Num_No_Tie_CPL_Test) {
    // test correct formating OPL load into file_data
    // std::cerr << "Begin CPL file load test" << std::endl;
    ASSERT_NO_THROW(blank_file_data->Load_File(good_cpl_one));
    int num_parties = blank_file_data->get_num_parties_();
    int num_seats = blank_file_data->get_num_seats_();
    int num_ballots = blank_file_data->get_num_ballots_();
    int num_cands = blank_file_data->get_num_candidates_();
    ASSERT_NO_THROW(blank_file_data->Convert_OPL_To_CPL());
    ASSERT_NO_THROW(blank_file_data->Calculate_Num_Seats());
    float quota = blank_file_data->get_quota_();

    Party_Data * parties = blank_file_data->get_party_list_();

    int expect_num_seats = 4;
    int expect_num_ballots = 16;
    int expect_num_cands = 10;
    float expect_quota = 4;
    int expect_seat_D = 1;
    int expect_seat_R = 2;
    int expect_seat_G = 1;
    int expect_seat_I = 0;

    EXPECT_EQ(num_seats, expect_num_seats);
    EXPECT_EQ(num_ballots, expect_num_ballots);
    EXPECT_EQ(quota, expect_quota)<<"quota";;
    EXPECT_EQ(parties[0].seats_,expect_seat_D)<<"R";
    EXPECT_EQ(parties[1].seats_,expect_seat_R)<<"D";
    EXPECT_EQ(parties[2].seats_,expect_seat_G)<<"G";
    EXPECT_EQ(parties[3].seats_,expect_seat_I)<<"I";
}

// Check that Convert_OPL_TO_CPL correctly sets num_parties_
// Philip
TEST_F(FileDataTest, Conversion_Num_Parties) {
  EXPECT_EQ(f1->get_num_parties_(), 3);
}

TEST_F(FileDataTest, Num_Rep) {
  for (int i = 0; i < f1->get_num_parties_(); i++) {
    if (prty[i].name_ == 'R') {
      rep = &prty[i];
      EXPECT_EQ(prty[i].num_candidates_, 3);
    }
  }
}

TEST_F(FileDataTest, Num_Dem) {
  for (int i = 0; i < f1->get_num_parties_(); i++) {
    if (prty[i].name_ == 'D') {
      dem = &prty[i];
      EXPECT_EQ(prty[i].num_candidates_, 2);
    }
  }
}

TEST_F(FileDataTest, Num_Ind) {
  for (int i = 0; i < f1->get_num_parties_(); i++) {
    if (prty[i].name_ == 'I') {
      ind = &prty[i];
      EXPECT_EQ(prty[i].num_candidates_, 1);
    }
  }
}

// Check that the candidates have been sorted in decreasing order
// Philip
TEST_F(FileDataTest, Sort_Rep) {
  EXPECT_EQ(strcmp(prty[0].candidates_[0].name_,"Phil"),  0);
  EXPECT_EQ(strcmp(prty[0].candidates_[1].name_,"Al"),    0);
  EXPECT_EQ(strcmp(prty[0].candidates_[2].name_,"Barry"), 0);
}

TEST_F(FileDataTest, Sort_Dem) {
  dem = &prty[1];
  EXPECT_EQ(strcmp(dem->candidates_[0].name_,"Sally"), 0);
  EXPECT_EQ(strcmp(dem->candidates_[1].name_,"Tom"),   0);
}

TEST_F(FileDataTest, Sort_Ind) {
  ind = &prty[2];
  EXPECT_EQ(strcmp(ind->candidates_[0].name_,"Troy"),  0);
}
// Check that rank is correctly calculated for each candidate in opl
// Philip
TEST_F(FileDataTest, Rank_Rep) {
  rep = &prty[0];
  EXPECT_EQ(rep->candidates_[0].party_rank_, 1);
  EXPECT_EQ(rep->candidates_[1].party_rank_, 2);
  EXPECT_EQ(rep->candidates_[2].party_rank_, 3);
}

TEST_F(FileDataTest, Rank_Dem) {
  dem = &prty[1];
  EXPECT_EQ(dem->candidates_[0].party_rank_, 1);
  EXPECT_EQ(dem->candidates_[1].party_rank_, 2);
}

TEST_F(FileDataTest, Rank_Ind) {
  ind = &prty[2];
  EXPECT_EQ(ind->candidates_[0].party_rank_, 1);
}
// Check that the random distribution is correct (even)
// Philip
TEST_F(FileDataTest, Random_Distro) {
  int run_n = 100000;
  int * ranks = new int[4];
  float avg = 0;
  float dist_from_avg = 0;
  for (int j = 0; j < 4; j++) {
    ranks[j] = 0;
  }
  for (int i = 0; i < run_n; i++) {
    f2->Convert_OPL_To_CPL();
    prty2 = f2->get_party_list_();
    for (int j = 0; j < 4; j++) {
      if (strcmp(prty2[0].candidates_[j].name_, "A") == 0) {
	ranks[0] += prty2[0].candidates_[j].party_rank_;
      } else if (strcmp(prty2[0].candidates_[j].name_, "B") == 0) {
	ranks[1] += prty2[0].candidates_[j].party_rank_;
      } else if (strcmp(prty2[0].candidates_[j].name_, "C") == 0) {
	ranks[2] += prty2[0].candidates_[j].party_rank_;
      } else if (strcmp(prty2[0].candidates_[j].name_, "D") == 0) {
	ranks[3] += prty2[0].candidates_[j].party_rank_;
      }
    }
    if (i != run_n - 1) {
      delete [] prty2;
    }
  }
  // Create an average
  for (int j = 0; j < 4; j++) {
    avg += ranks[j];
  }
  avg = avg / 4;
  // ensure that all values are within 2.5% of the average
  for (int j = 0; j < 4; j++) {
    dist_from_avg = ranks[j] - avg;
    EXPECT_EQ((dist_from_avg > (avg * 0.05) || dist_from_avg < (avg * 0.05)), true);
  }

  delete [] ranks;
}
