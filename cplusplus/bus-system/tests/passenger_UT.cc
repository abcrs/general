/*
 * Students: Use this file as a guide to writing your own unit tests.
 * See the project instructions for more information on which classes
 * and methods must be tested.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PassengerTests : public ::testing::Test {
protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  Passenger *passenger, *passenger1, *passenger2;

  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();

    passenger = new Passenger();
    passenger1 = new Passenger(11, "Billy Bob");
    passenger2 = new Passenger(12, "Jilly Jane");
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete passenger;
    delete passenger1;
    delete passenger2;
    passenger = NULL;
    passenger1 = NULL;
    passenger2 = NULL;
    pass_loader = NULL;
    pass_unloader = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PassengerTests, Constructor) {
  int expected_time = 0;
  int actual_time = passenger->GetTotalWait();
  int expected_stop = -1;
  int actual_stop = passenger->GetDestination();
  EXPECT_EQ(passenger->IsOnBus(), false);
  EXPECT_EQ(expected_time, actual_time);
  EXPECT_EQ(expected_stop, actual_stop);
};

TEST_F(PassengerTests, ReportNames) {
  std::string expected_name_1 = "Name: Nobody";
  std::string expected_name_2 = "Name: Billy Bob";
  testing::internal::CaptureStdout();
  passenger->Report(std::cout);
  std::string actual_name_1 = testing::internal::GetCapturedStdout();
  testing::internal::CaptureStdout();
  passenger1->Report(std::cout);
  std::string actual_name_2 = testing::internal::GetCapturedStdout();
  int p1 = actual_name_1.find(expected_name_1);
  int p2 = actual_name_2.find(expected_name_2);
  EXPECT_GE(p1, 0);
  EXPECT_GE(p2, 0);
};

TEST_F(PassengerTests, IsOnBus) {
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);
};

TEST_F(PassengerTests, GetOnBus) {
  EXPECT_EQ(passenger1->IsOnBus(), false);
  passenger1->GetOnBus();
  EXPECT_EQ(passenger1->IsOnBus(), true);
};

TEST_F(PassengerTests, UpdateStopTime) {
  EXPECT_EQ(passenger2->GetTotalWait(), 0);
  passenger2->Update();
  passenger2->Update();
  EXPECT_EQ(passenger2->GetTotalWait(), 2);
};

TEST_F(PassengerTests, UpdateBusTime) {
  EXPECT_EQ(passenger2->GetTotalWait(), 0);
  passenger2->GetOnBus();
  passenger2->Update();
  passenger2->Update();
  EXPECT_EQ(passenger2->GetTotalWait(), 3);
};

TEST_F(PassengerTests, UpdateBothTime) {
  EXPECT_EQ(passenger2->GetTotalWait(), 0);
  passenger2->Update();
  passenger2->Update();
  passenger2->GetOnBus();
  passenger2->Update();
  passenger2->Update();
  EXPECT_EQ(passenger2->GetTotalWait(), 5);
};
