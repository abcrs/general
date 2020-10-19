/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class StopTests : public ::testing::Test {
protected:
  Stop *stop1, *stop2;

  virtual void SetUp() {
    stop1 = new Stop(1);
    stop2 = new Stop(2, 45.0, -93.0);
  }

  virtual void TearDown() {
    delete stop1;
    delete stop2;

    stop1 = NULL;
    stop2 = NULL;
  }
};

TEST_F(StopTests, BaseConstructor) {
  int expected_id = 1;
  double expected_lon = 44.973723;
  double expected_lat = -93.235365;
  EXPECT_EQ(stop1->GetId(), expected_id);
  EXPECT_EQ(stop1->GetLongitude(), expected_lon);
  EXPECT_EQ(stop1->GetLatitude(), expected_lat);
};

TEST_F(StopTests, WholeConstructor) {
  int expected_id = 2;
  double expected_lon = 45.0;
  double expected_lat = -93.0;
  EXPECT_EQ(stop2->GetId(), expected_id);
  EXPECT_EQ(stop2->GetLongitude(), expected_lon);
  EXPECT_EQ(stop2->GetLatitude(), expected_lat);
};
