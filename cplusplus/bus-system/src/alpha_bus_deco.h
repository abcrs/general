/**
 * @file alpha_bus_deco.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#ifndef SRC_ALPHA_BUS_DECO_H_
#define SRC_ALPHA_BUS_DECO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/bus_decorator.h"

class Bus;
class Route;
class Stop;
class Passenger;
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
class AlphaBusDecorator : public BusDecorator {
 public:
    /**
     * @brief Constructor to start the decorator
     *
     * Contains an object of the ibus interface type, which is to be decorated
     *
     * @param[in] A ibus object
     */
    explicit AlphaBusDecorator(IBus * bus): BusDecorator(bus) {}
    /**
     * @brief Returns if bus if finished with all routes
     *
     * Returns a boolean that notifies if bus is finished travelling
     *
     * @return is bus finished
     */
    bool IsTripComplete() override { return bus_deco_->IsTripComplete(); }
    /**
     * @brief Add passenger to bus
     *
     * Add a new passenger to the bus, update relevant data
     *
     * @param[in] new_passenger, new passenger to be added
     *
     * @return boolean that shows if passenger successfully added
     */
    bool LoadPassenger(Passenger * p) override
        { return bus_deco_->LoadPassenger(p); }
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
    bool Move() override { return bus_deco_->Move(); }
    /**
     * @brief Update bus
     *
     * Call Move and UpdateBusData methods
     */
    void Update() override { bus_deco_->Update(); }
    /**
     * @brief Report on status of bus
     *
     * Prints to passed in ostream the current status of the bus
     *
     * @param[in] out, stream to send information to
     */
    void Report(std::ostream& out) override { bus_deco_->Report(out); }

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
    void UpdateBusData() override { bus_deco_->UpdateBusData(); }
    /**
     * @brief Gives bus_data_
     *
     * Gives bus data
     *
     * @return data of bus
     */
    BusData GetBusData() const override { return bus_deco_->GetBusData(); }
    /**
     * @brief Gives name_
     *
     * Gives name
     *
     * @return name of bus
     */
    std::string GetName() const override { return bus_deco_->GetName(); }
    /**
     * @brief Gives next_stop_
     *
     * Gives next stop
     *
     * @return next stop that bus will visit
     */
    Stop * GetNextStop() const override { return bus_deco_->GetNextStop(); }
    /**
     * @brief Gives passengers_.size
     *
     * Gives number of passengers on bus
     *
     * @return Amount of passengers on the bus
     */
    size_t GetNumPassengers() const override
        { return bus_deco_->GetNumPassengers(); }
    /**
     * @brief Gives passenger_max_capacity_
     *
     * Gives number of passengers that can fit on bus
     *
     * @return Max capacity of bus
     */
    int GetCapacity() const override { return bus_deco_->GetCapacity(); }
    /**
     * @brief Set the bus color
     *
     * Set the bus color, which is sent from the decorator
     *
     * @param[in] A struct containing the correct color
     */
    void SetColor(Color n_color) override { bus_deco_->SetColor(n_color); }
    /**
     * @brief Set the bus color intensity
     *
     * The purpose for this class
     *
     * @param[in] A struct containing the correct intensity
     */
    void SetAlpha(int a) override;
    /**
     * @brief Determine if Outgoing Route is finished
     *
     * Used to determine color when decorating
     *
     * @return true if outgoing route done, false otherwise
     */
    bool OutRouteDone() override { return bus_deco_->OutRouteDone(); }
};
#endif  // SRC_ALPHA_BUS_DECO_H_
