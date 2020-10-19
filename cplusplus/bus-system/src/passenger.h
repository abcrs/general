/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for passenger interaction on bus.
 *
 * Contains different methods to update passengers on the bus,
 * keep track of passengers on the bus, and determine destinations.
 */
class Passenger {  // : public Reporter {
 public:
    /**
     * @brief Passenger constructor
     *
     * Creates a passenger object
     *
     * @param[in] desintation_stop, passenger destination
     * @param[in] name, passenger name
     **/
    explicit Passenger(int desintation_stop = -1, std::string = "Nobody");
    /**
     * @brief Increments wait_at_stop_
     *
     * Keeps track of amount of time the passenger has been on the bus
     **/
    void Update();
    /**
     * @brief Starts passenger on bus
     *
     * Starts passenger on bus
     **/
    void GetOnBus();
    /**
     * @brief Determines total time waiting
     *
     * @return wait_at_stop_ counter
     **/
    int GetTotalWait() const;
    /**
     * @brief Determines if passenger is on the bus
     *
     * @return returns false
     **/
    bool IsOnBus() const;
    /**
     * @brief Gives destination_stop_id_
     *
     * Gives passenger destination
     *
     * @return gives passenger specific destination_stop_id_
     **/
    int GetDestination() const;
    /**
     * @brief Outputs passenger information
     *
     * Outputs to ostream object information on passenger and details about wait
     *
     * @param[in] out, ostream object where information is sent
     **/
    void Report(std::ostream&) const;

 private:
      std::string name_;
      int destination_stop_id_;
      int wait_at_stop_;
      int time_on_bus_;
      int id_;
      static int count_;  // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
