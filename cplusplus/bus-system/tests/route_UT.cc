/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/route.h"
#include "../src/random_passenger_generator.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class RouteTests : public ::testing::Test {
protected:
  Stop *stop1, *stop2, *stop3;
  Stop **stops;
  double * distances;
  RandomPassengerGenerator * blank_pass_gen;
  Route *route1;;

  virtual void SetUp() {
    stop1 = new Stop(1);
    stop2 = new Stop(2);
    stop3 = new Stop(3);

    stops = new Stop*[3];
    stops[0] = stop1;
    stops[1] = stop2;
    stops[2] = stop3;

    distances = new double[3];
    distances[0] = 1.0;
    distances[1] = 1.5;
    distances[2] = 2.0;

    route1 = new Route("one", stops, distances, 3, blank_pass_gen);
  }

  virtual void TearDown() {
    delete stop1;
    delete stop2;
    delete stop3;
    delete stops;
    delete distances;
    delete route1;

    stop1 = NULL;
    stop2 = NULL;
    stop3 = NULL;
    stops = NULL;
    distances = NULL;
    route1 = NULL;
  }
};

TEST_F(RouteTests, Constructor) {
  std::string expected_name = "one";
  double expected_distance = 4.5;
  std::list<Stop *> expected_stops;
  expected_stops.push_back(stop1);
  expected_stops.push_back(stop2);
  expected_stops.push_back(stop3);
  std::list<Stop *> actual_stops = route1->GetStops();
  std::list<Stop *>::iterator it = expected_stops.begin();
  std::list<Stop *>::iterator it1 = actual_stops.begin();
  EXPECT_EQ((*it)->GetId(), (*it1)->GetId());
  it++;
  it1++;
  EXPECT_EQ((*it)->GetId(), (*it1)->GetId());
  it++;
  it1++;
  EXPECT_EQ((*it)->GetId(), (*it1)->GetId());
  EXPECT_EQ(route1->GetStops(), expected_stops);
  EXPECT_EQ(route1->GetName(), expected_name);
  EXPECT_EQ(route1->GetTotalRouteDistance(), expected_distance);
};

TEST_F(RouteTests, IsAtEnd) {
  EXPECT_EQ(route1->IsAtEnd(), false);
  route1->ToNextStop();
  route1->ToNextStop();
  route1->ToNextStop();
  EXPECT_EQ(route1->IsAtEnd(), true);
};
