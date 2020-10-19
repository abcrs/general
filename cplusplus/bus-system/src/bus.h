/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <list>

#include "src/ibus.h"

#include "src/route.h"
#include "src/stop.h"
#include "src/passenger.h"
#include "src/passenger_unloader.h"
#include "src/passenger_loader.h"

class Route;
class Stop;
class PassengerUnloader;
class PassengerLoader;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Bus class maintains a bus
 *
 * Maintains a list of passengers that are on the bus
 * Also has two routes that the bus travels on
 * Takes passengers to their destinations
 */
class Bus : public IBus {
 public:
    /**
     * @brief Bus constructor
     *
     * Create a bus object
     *
     * @param[in] name, bus name
     * @param[in] out, outgoing bus route
     * @param[in] in, incoming bus route
     * @param[in] capacity, total passengers that can fit on bus
     * @param[in] speed, bus speed along routes
     */
    Bus(std::string name, Route * out, Route * in, int capacity = 60,
      double speed = 1, std::string type = "Medium");
    /**
     * @brief Returns if bus if finished with all routes
     *
     * Returns a boolean that notifies if bus is finished travelling
     *
     * @return is bus finished
     */
    bool IsTripComplete() override;
    /**
     * @brief Add passenger to bus
     *
     * Add a new passenger to the bus, update relevant data
     *
     * @param[in] new_passenger, new passenger to be added
     *
     * @return boolean that shows if passenger successfully added
     */
    bool LoadPassenger(Passenger * p) override;
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
    bool Move() override;
    /**
     * @brief Update bus
     *
     * Call Move and UpdateBusData methods
     */
    void Update() override;
    /**
     * @brief Report on status of bus
     *
     * Prints to passed in ostream the current status of the bus
     *
     * @param[in] out, stream to send information to
     */
    void Report(std::ostream& out) override;

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
    void UpdateBusData() override;
    /**
     * @brief Gives bus_data_
     *
     * Gives bus data
     *
     * @return data of bus
     */
    BusData GetBusData() const override;
    /**
     * @brief Gives name_
     *
     * Gives name
     *
     * @return name of bus
     */
    std::string GetName() const override { return name_; }
    /**
     * @brief Gives next_stop_
     *
     * Gives next stop
     *
     * @return next stop that bus will visit
     */
    Stop * GetNextStop() const override { return next_stop_; }
    /**
     * @brief Gives passengers_.size
     *
     * Gives number of passengers on bus
     *
     * @return Amount of passengers on the bus
     */
    size_t GetNumPassengers() const override { return passengers_.size(); }
    /**
     * @brief Gives passenger_max_capacity_
     *
     * Gives number of passengers that can fit on bus
     *
     * @return Max capacity of bus
     */
    int GetCapacity() const override { return passenger_max_capacity_; }
    /**
     * @brief Set the bus color
     *
     * Set the bus color, which is sent from the decorator
     *
     * @param[in] A struct containing the correct color
     */
    void SetColor(Color n_color) override { bus_data_.color = n_color; }
    /**
     * @brief Set the bus color intensity
     *
     * Set the bus color intensity, which is sent from the decorator
     *
     * @param[in] A struct containing the correct intensity
     */
    void SetAlpha(int a) override { bus_data_.color.alpha = a; }
    /**
     * @brief Determine if Outgoing Route is finished
     *
     * Used to determine color when decorating
     *
     * @return true if outgoing route done, false otherwise
     */
     bool OutRouteDone() override { return outgoing_route_done_; }

 private:
    /**
     * @brief Unloads passengers from bus
     *
     * Uses unloader_ to unload passengers at the next stop
     *
     * @return Number of passengers unloaded
     */
    int UnloadPassengers();  // returning revenue delta
    // bool Refuel();
    PassengerUnloader * unloader_;
    PassengerLoader * loader_;
    std::list<Passenger *> passengers_;
    int total_passengers_;  // Running total of passengers who've ridden on bus
    int passenger_max_capacity_;
    // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
    // double fuel_;   // may not be necessary for our simulation
    // double max_fuel_;
    std::string name_;
    std::string type_;
    double speed_;  // could also be called "distance travelled in one time step
    Route * outgoing_route_;
    Route * incoming_route_;
    bool outgoing_route_done_;  // bool if the first route is finished
    double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
    Stop * next_stop_;
    // bool trip_complete_;  // [DERIVED data] when BOTH routes are at end, trip
    // is complete

    // Vis data for bus
    BusData bus_data_;
};
#endif  // SRC_BUS_H_
