/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/bus.h"
#include "../src/random_passenger_generator.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BusTests : public ::testing::Test {
protected:
  Bus * bus1;
  Bus * bus2;
  Bus * bus3;

  Route * route_out;
  Route * route_in;

  Stop * stop1;
  Stop * stop2;
  Stop * stop3;
  Stop * stop4;

  Stop ** stops_1, ** stops_2;

  Passenger * passenger1;

  double * distances;

  RandomPassengerGenerator * blank_pass_gen;

  virtual void SetUp() {
    stop1 = new Stop(1);
    stop2 = new Stop(2);
    stop3 = new Stop(3);
    stop4 = new Stop(4);

    stops_1 = new Stop*[2];
    stops_1[0] = stop1;
    stops_1[1] = stop2;

    stops_2 = new Stop*[2];
    stops_2[0] = stop3;
    stops_2[1] = stop4;

    passenger1 = new Passenger(13, "Jo");

    distances = new double[2];
    distances[0] = 1.0;
    distances[1] = 1.5;

    route_out = new Route("one", stops_1, distances, 2, blank_pass_gen);
    route_in = new Route("two", stops_2, distances, 2, blank_pass_gen);

    bus1 = new Bus("4", route_out, route_in, 20, 1.0);
    bus2 = new Bus("2", route_out, route_in, 40, 1.0);
    bus3 = new Bus("123", route_out, route_in, 60, 0);
  }

  virtual void TearDown() {
    delete bus1;
    delete bus2;
    delete bus3;
    delete stop1;
    delete stop2;
    delete stop3;
    delete stops_1;
    delete stops_2;
    delete distances;
    delete route_out;
    delete route_in;

    bus1 = NULL;
    bus2 = NULL;
    bus3 = NULL;
    stop1 = NULL;
    stop2 = NULL;
    stop3 = NULL;
    stops_1 = NULL;
    stops_2 = NULL;
    distances = NULL;
    route_out = NULL;
    route_in = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 TEST_F(BusTests, Constructor) {
   std::string expected_name = "4";
   int expected_capacity = 20;
   int expected_passenger = 0;

   EXPECT_EQ(expected_name, bus1->GetName());
   EXPECT_EQ(expected_capacity, bus1->GetCapacity());
   EXPECT_EQ(expected_passenger, bus1->GetNumPassengers());
   EXPECT_EQ(stop1, bus1->GetNextStop());
 };

 TEST_F(BusTests, IsTripComplete) {
   EXPECT_EQ(false, bus2->IsTripComplete());
   EXPECT_EQ(false, bus2->IsTripComplete());
 };

TEST_F(BusTests, Move) {
  EXPECT_EQ(false, bus3->Move());
  bus2->Move();
  bus2->Move();
  bus2->Move();
  bus2->Move();
  bus2->Move();
  EXPECT_EQ(true, bus2->Move());
}

TEST_F(BusTests, LoadPassenger) {
  EXPECT_EQ(bus1->LoadPassenger(passenger1), true);
}
