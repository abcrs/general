/**
 * @file large_bus.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#ifndef SRC_BUS_TYPE_H_
#define SRC_BUS_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/bus.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class to create Large capacity busses
 *
 * Large capacity busses are created and used by simulation
 **/
class LargeBus : public Bus {
 public:
/**
 * @brief LargeBus constructor
 *
 * Creates a LargeBus, which is a bus with max capacity
 *
 * @param[in] name, name of bus
 * @param[in] out, outgoing route for bus
 * @param[in] in, incoming route for bus
 * @param[in] speed, speed of bus
 **/
  LargeBus(std::string name, Route * out, Route * in, double speed = 1) :
       Bus(name, out, in, 90, speed, "Large") { }
};

class RegularBus : public Bus {
 public:
/**
 * @brief MediumBus constructor
 *
 * Creates a MediumBus, which is a bus with medium capacity
 *
 * @param[in] name, name of bus
 * @param[in] out, outgoing route for bus
 * @param[in] in, incoming route for bus
 * @param[in] speed, speed of bus
 **/
  RegularBus(std::string name, Route * out, Route * in, double speed = 1) :
        Bus(name, out, in, 60, speed, "Medium") { }
};

/**
 * @brief Class to create small capacity busses
 *
 * Small capacity busses are created and used by simulation
 **/
class SmallBus : public Bus {
 public:
/**
 * @brief SmallBus constructor
 *
 * Creates a SmallBus, which is a bus with the least capacity
 *
 * @param[in] name, name of bus
 * @param[in] out, outgoing route for bus
 * @param[in] in, incoming route for bus
 * @param[in] speed, speed of bus
 **/
  SmallBus(std::string name, Route * out, Route * in, double speed = 1) :
       Bus(name, out, in, 30, speed, "Small") { }
};

#endif  // SRC_BUS_TYPE_H_
