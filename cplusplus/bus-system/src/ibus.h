/**
 * @file ibus.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#ifndef SRC_IBUS_H_
#define SRC_IBUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <list>
#include <string>

#include "src/iobservable.h"

#include "src/data_structs.h"

class Route;
class Passenger;
class Stop;
class PassengerUnloader;
class PassengerLoader;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief: IBus is an interface for the Bus class and its decorator
 *
 * Other classes inherit IBus, as to allow the busses to be decorated
 **/
class IBus : public IObservable {
 public:
    /**
     * @brief Returns if bus if finished with all routes
     *
     * Returns a boolean that notifies if bus is finished travelling
     *
     * @return is bus finished
     */
    virtual bool IsTripComplete() = 0;
    /**
     * @brief Add passenger to bus
     *
     * Add a new passenger to the bus, update relevant data
     *
     * @param[in] new_passenger, new passenger to be added
     *
     * @return boolean that shows if passenger successfully added
     */
    virtual bool LoadPassenger(Passenger *) = 0;
    /**
     * @brief Move bus to next stop
     *
     * Move bus to next stop on route
     * Update all passengers getting on and off of bus
     *
     * @param[in] Passenger object to be added to bus
     *
     * @return boolean that shows if bus moved to next stop
     */
    virtual bool Move() = 0;
    /**
     * @brief Update bus
     *
     * Call Move and UpdateBusData methods
     */
    virtual void Update() = 0;
    /**
     * @brief Report on status of bus
     *
     * Prints to passed in ostream the current status of the bus
     *
     * @param[in] out, stream to send information to
     */
    virtual void Report(std::ostream&) = 0;

    // Vis Getters
    /**
     * @brief Update bus data based on movement
     *
     * Update all important bus data based on the last movement
     * If at end of outgoing route, change to incoming route
     * Update bus position based on distance to next stop
     *
     * @param[in] ostream data to send data from the report
     */
    virtual void UpdateBusData() = 0;
    /**
     * @brief Gives bus_data_
     *
     * Gives bus data
     *
     * @return data of bus
     */
    virtual BusData GetBusData() const = 0;
    /**
     * @brief Gives name_
     *
     * Gives name
     *
     * @return name of bus
     */
    virtual std::string GetName() const = 0;
    /**
     * @brief Gives next_stop_
     *
     * Gives next stop
     *
     * @return next stop that bus will visit
     */
    virtual Stop * GetNextStop() const = 0;
    /**
     * @brief Gives passengers_.size
     *
     * Gives number of passengers on bus
     *
     * @return Amount of passengers on the bus
     */
    virtual size_t GetNumPassengers() const = 0;
    /**
     * @brief Gives passenger_max_capacity_
     *
     * Gives number of passengers that can fit on bus
     *
     * @return Max capacity of bus
     */
    virtual int GetCapacity() const = 0;
    /**
     * @brief Set the bus color
     *
     * Set the bus color, which is sent from the decorator
     *
     * @param[in] A struct containing the correct color
     */
    virtual void SetColor(Color n_color) = 0;
    /**
     * @brief Set the bus color intensity
     *
     * Set the bus color intensity, which is sent from the decorator
     *
     * @param[in] A struct containing the correct intensity
     */
    virtual void SetAlpha(int a) = 0;
    /**
     * @brief Determine if Outgoing Route is finished
     *
     * Used to determine color when decorating
     *
     * @return true if outgoing route done, false otherwise
     */
     virtual bool OutRouteDone() = 0;
};
#endif  // SRC_IBUS_H_
