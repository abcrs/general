/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <string>
#include <vector>

#include "src/data_structs.h"

#include "src/passenger_generator.h"
#include "src/stop.h"

class PassengerGenerator;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Route {
 public:
/**
 * @brief Route constructor
 *
 * Create a route object
 *
 * @param[in] name, name of the route
 * @param[in] stops, 'list' of stops that are in the route
 * @param[in] distances, 'list' of distances between stops
 * @param[in] num_stops, number of stops in the route
 * @param[in] generator, a PassengerGenerator object to add passengers to stops
 */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
/**
 * @brief Clones a route
 *
 * Clones everything in a route to create a new object that is a copy
 *
 * @return A new route object that is a clone of the original
 */
  Route * Clone();
/**
 * @brief Updates route
 *
 * Add new passengers to the route
 * Iterate through the list of stops and update each one
 * Update RouteData object
 */
  void Update();
/**
 * @brief Outputs data from the route
 *
 * Outputs to ostream object information about the route
 *
 * param[in] out, ostream object where information is sent
 */
  void Report(std::ostream&);
/**
 * @brief Determines if route is finished
 *
 * Checks if stop index is beyond the max
 *
 * @return boolean that shows if route has visited all stops
 */
  bool IsAtEnd() const;

/**
 * @brief Returns previous visited stop
 *
 * Returns the previously visited stop, or the first stop if none visited yet
 *
 * @return The stop that was last visited
 */
  Stop *  PrevStop();  // Returns stop before destination stop
/**
 * @brief Increase iterator to next stop
 *
 * If route has not reached its end, goes to next stop
 */
  void ToNextStop();  // Change destination_stop_ to next stop
/**
 * @brief Gives destination_stop_
 *
 * Gives the destination stop
 *
 * @return stop object of the destination stop
 */
  Stop * GetDestinationStop() const;    // Get pointer to next stop
/**
 * @brief Gives total distance between all stops
 *
 * Iterates through list of distances and adds them all up
 *
 * @return Total of all distances between stops, summed
 */
  double GetTotalRouteDistance() const;
/**
 * @brief Gives distance to next stop
 *
 * Returns the value of the distance between current stop and next stop
 *
 * @return Distance to the next stop
 */
  double GetNextStopDistance() const;

  // Vis Getters
/**
 * @brief Gives name_
 *
 * Gives name of route
 *
 * @return Name of route
 */
  std::string GetName() const { return name_; }
/**
 * @brief Gives stops_
 *
 * Gives list of stops on the route
 *
 * @return The route's list of stop
 */
  std::list<Stop *> GetStops() const { return stops_; }
/**
 * @brief Update RouteData object
 *
 * Updates each member of the route_data_ object
 */
  void UpdateRouteData();
/**
 * @brief Gives route_data_
 *
 * Gives the route data object
 *
 * @return Gives the data about the route
 */
  RouteData GetRouteData() const;

 private:
/**
 * @brief Generate new passengers for the route
 *
 * Uses the PassengerGenerator to generate new passengers for the route
 *
 * @param Gives the number of new passengers created
 */
  int GenerateNewPassengers();       // generates passengers on its route
  PassengerGenerator * generator_;
  std::list<Stop *> stops_;
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  int destination_stop_index_;  // always starts at zero, no init needed
  Stop * destination_stop_;
  // double trip_time_; // derived data - total distance travelled on route

  RouteData route_data_;
};
#endif  // SRC_ROUTE_H_
