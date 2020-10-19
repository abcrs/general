/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_STOP_H_
#define SRC_STOP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <vector>

#include "src/passenger.h"
#include "src/bus.h"

class Bus;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class to hold information about stops
 *
 * Contains information about location of stop
 * Also holds passengers waiting to be picked up
 */
class Stop : public IObservable {
 public:
/**
 * @brief Stop constructor
 *
 * Creates a stop object
 *
 * @param[in] id_, integer id of the stop
 * @param[in] latitude_, latitude of the stop
 * @param[in] longitude_, longitude of the stop
 */
  explicit Stop(int, double = 44.973723, double = -93.235365);
/**
 * @brief Add passengers to a bus
 *
 * Loads passengers from the stop to a bus that has arrived
 *
 * @return The number of passengers loaded on the bus
 */
  int LoadPassengers(Bus *);
/**
 * @brief Add a passenger to a stop
 *
 * Add passenger to the list of passengers at the stop
 *
 * @param[in] pass, passenger to be added
 *
 * @return The number of passengers added
 */
  int AddPassengers(Passenger *);
/**
 * @brief Update the stop
 *
 * Update each passenger at the stop (increase wait time)
 */
  void Update();
/**
 * @brief Gives id_
 *
 * Gives id of the stop
 *
 * @return The id of the stop
 */
  int GetId() const;
/**
 * @brief Outputs information about the stop
 *
 * Outputs to an ostream object information about the stop
 *
 * @param[in] The ostream object where information will be sent
 */
  void Report(std::ostream&) const;

  // Vis Getters
/**
 * @brief Gives longitude_
 *
 * Gives longitude of stop
 *
 * @return The longitude of the stop
 */
  double GetLongitude() const { return longitude_; }
/**
 * @brief Gives latitude_
 *
 * Gives latitude of stop
 *
 * @return The latitude of the stop
 */
  double GetLatitude() const { return latitude_; }
/**
 * @brief Gives the passengers_.size()
 *
 * Gives the number of passengers waiting at the stop
 *
 * @return Gives the passengers waiting at the stop
 */
  size_t GetNumPassengersPresent() { return passengers_.size(); }

 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  double longitude_;
  double latitude_;  // are we using long/lat coords?
  StopData stop_data_;
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
