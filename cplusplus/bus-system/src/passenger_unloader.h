/**
 * @file passenger_unloader.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_UNLOADER_H_
#define SRC_PASSENGER_UNLOADER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <list>
#include <sstream>

#include "src/passenger.h"
#include "src/stop.h"
#include "src/file_writer.h"
#include "src/data_parser.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class to handle unloading of passengers
 *
 * Class must unload passengers on to a bus via the passenger list the bus has
 */
class PassengerUnloader {
 public:
    /**
     * @brief Unloads passengers from the bus and adds to the stop
     *
     * Iterates through list of passengers and removes any who have found their spot
     * If passenger leaves bus, add passenger to the stop
     *
     * @return The number of passengers unloaded
     */
    int UnloadPassengers(std::list<Passenger*>* passengers,
                         Stop * current_stop);

 private:
    std::string pass_data_file_ = "PassData.csv";
    FileWriter * pass_data_writer_ = pass_data_writer_->GetWriter();
};
#endif  // SRC_PASSENGER_UNLOADER_H_
