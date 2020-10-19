/**
 * @file random_passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_RANDOM_PASSENGER_GENERATOR_H_
#define SRC_RANDOM_PASSENGER_GENERATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <random>
#include <ctime>

#include "src/passenger_generator.h"
#include "src/stop.h"

class Stop;  // forward declaration

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief RandomPassengerGenerator extends PassengerGenerator class
 *
 * Generates passengers randomly
 */
class RandomPassengerGenerator : public PassengerGenerator{
 public:
/**
 * @brief RandomPassengerGenerator constructor
 *
 * Creates a RandomPassengerGenerator object
 *
 * @param[in] probs, list of doubles of probabilities for passengers at stops
 * @param[in] stops, list of stops where passengers can be
 */
  RandomPassengerGenerator(std::list<double>, std::list<Stop *>);
/**
 * @brief Method to generate passengers
 *
 * Generates passengers randomly, based on stop locatioan
 * And probability that passengers appear at each stop
 *
 * @return number of passengers passengers_added
 */
  int GeneratePassengers() override;

 private:
  static std:: minstd_rand0 my_rand;
};

#endif  // SRC_RANDOM_PASSENGER_GENERATOR_H_
