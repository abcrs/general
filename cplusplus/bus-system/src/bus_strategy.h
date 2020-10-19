/**
 * @file bus_strategy.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#ifndef SRC_BUS_STRATEGY_H_
#define SRC_BUS_STRATEGY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <ctime>
#include <iostream>

#include "src/bus.h"
#include "src/bus_type.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class to handle bus deployment strategy
  *
  * Keeps track of time and returns the strategy needed based on time
  **/
class Strategy {
 public:
    /**
     * @brief Returns new bus object
     *
     * Virtual method to set up for other strategies
     *
     * return int of which type of bus should be generated
     **/
    virtual int PickBus() = 0;

    /**
     * @brief Returns hour of current time
     *
     * Only relevant time is the hour, so returns the current hour of the day
     *
     * @return int, current hour of the day
     **/
    int GetTime();
};

class MorningStrategy : public Strategy {
 public:
    /**
     * @brief Generates new bus
     *
     * Generates new bus, and uses strategy to determine what size
     *
     * return int of which type of bus should be generated
     **/
    int PickBus() override;
};

class AfternoonStrategy : public Strategy {
 public:
    /**
     * @brief Generates new bus
     *
     * Generates new bus, and uses strategy to determine what size
     *
     * return int of which type of bus should be generated
     **/
    int PickBus() override;
};

class EveningStrategy : public Strategy {
 public:
    /**
     * @brief Generates new bus
     *
     * Generates new bus, and uses strategy to determine what size
     *
     * return int of which type of bus should be generated
     **/
    int PickBus() override;
};

class OvernightStrategy : public Strategy {
 public:
    /**
     * @brief Generates new bus
     *
     * Generates new bus, and uses strategy to determine what size
     *
     * return int of which type of bus should be generated
     **/
    int PickBus() override;
};

#endif  // SRC_BUS_STRATEGY_H_
