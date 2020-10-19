/**
 * @file bus_factory.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#ifndef SRC_BUS_FACTORY_H_
#define SRC_BUS_FACTORY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/bus.h"
#include "src/bus_strategy.h"
#include "src/bus_type.h"

#include <string>
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the generation of busses
 *
 * Generates busses to run through the simulation
 **/
class BusFactory {
 public:
    /**
     * @brief: BusFactory constructor
     *
     * Creates a BusFactory object for use by other classes
     **/
    BusFactory(Route * outbound, Route * inbound, double speed);
    /**
     * @brief Generate new busses
     *
     * Uses a random number to generate a new bus based on capacity
     * Returns bus of that size
     *
     * @return Bus, newly created bus object
     **/
    Bus * Generate(std::string name);
    /**
     * @brief Update routes held in the bus factory
     *
     * Update the routes to change which routes busses go on
     *
     * @param[in] out a new outbound route
     * @param[in] in a new inbound route
     **/
    void UpdateRoutes(Route * out, Route * in);
    /**
     * @brief Picks the current strategy to use
     *
     * Uses the time to pick the correct strategy based on current time
     *
     * @param[out] Returns relevant Strategy
     **/
    Strategy * PickStrategy();

 private:
    Route * outbound_;
    Route * inbound_;
    double speed_;
    Strategy * strategy_;
};

#endif  // SRC_BUS_FACTORY_H_
