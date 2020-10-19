/**
 * @file bus.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/

#ifndef WEB_VISUALIZATION_SIMULATOR_H_
#define WEB_VISUALIZATION_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <list>
#include <string>

#include "web_code/web/web_interface.h"
#include "src/config_manager.h"
#include "src/ibus.h"
#include "src/bus_factory.h"
#include "src/bus_decorator.h"
#include "src/alpha_bus_deco.h"
#include "src/maroon_bus_deco.h"
#include "src/gold_bus_deco.h"
#include "src/data_parser.h"
#include "src/file_writer.h"

class Route;
class Bus;
class Stop;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class VisualizationSimulator {
 public:
    /**
     * @brief Constructor for VisualizationSimulator
     *
     * Constructs VisSim object
     * Sets object values of webInterface_ and configManager_
     *
     * @param[in] WebInterface interface to interact with web page
     * @param[in] ConfigManager manages route information
     **/
    VisualizationSimulator(WebInterface*, ConfigManager*);

    /**
     * @brief Destruct VisSim
     *
     * Destructor for VisSim object
     **/
    ~VisualizationSimulator();

    /**
     * @brief Begins simulation
     *
     * Starts the visual simulation
     * Sets local values for busStartTimings and numTimeSteps
     * Sets timeSinceLastBus_ vector to all 0
     * Sets simulationTimeElapsed_ to 0
     * Sets up routes using configManager_
     * Updates the routes and uses webInterface_ on them
     * Sets up busFactory_
     *
     * @param[in] busStartTimings a vector with times to start busses
     * @param[in] numTimeSteps how many time steps to take, input from server
     **/
    void Start(const std::vector<int>&, const int&);

    /**
     * @brief End of simulation, update final buses for the .csv
     *
     * For any buses not finished running when the simulation ends
     * Their information needs to be added to the ,csv
     */
    void End();

    /**
     * @brief Change pause value
     *
     * Change pause value, important elsewhere
     **/
    void Pause();

    /**
     * @brief Updates simluation
     *
     * If not paused, updates simulation
     * Increments time steps, prints updates
     * Generates new buses if necessary
     * Updates all buses by iterating through vector and calling relevant
     *   bus functions.
     * Updates the routes as necessary
     **/
    void Update();

    /**
     * @brief Clear any observers
     *
     * Iterate list of busses and remove any observers from each bus
     **/
    void ClearListeners();

    /**
     * @brief Add observer to bus
     *
     * Add an observer to the relevant bus
     *
     * @param[in] id bus which will have observer added to it
     * @param[in] observer that will be added to the bus
     **/
    void AddBusListener(std::string * id, IObserver * observer);

    /**
     * @brief Add observer to stop
     *
     * Add an observer to the relevant stop
     *
     * @param[in] id bus which will have observer added to it
     * @param[in] observer that will be added to the bus
     **/
    void AddStopListener(std::string * id, IObserver * observer);


 private:
    WebInterface* webInterface_;
    ConfigManager* configManager_;
    BusFactory* busFactory_;

    std::vector<int> busStartTimings_;
    std::vector<int> timeSinceLastBus_;
    int numTimeSteps_;
    int simulationTimeElapsed_;

    std::vector<Route *> prototypeRoutes_;
    std::vector<IBus *> busses_;

    std::string bus_data_file_ = "BusData.csv";
    std::string pass_data_file_ = "PassData.csv";
    FileWriter * bus_data_writer_;

    bool paused_ = false;

    int busId = 1000;
};

#endif  // WEB_VISUALIZATION_SIMULATOR_H_
