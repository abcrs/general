/**
 * @file my_web_server.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/
#ifndef WEB_MY_WEB_SERVER_H_
#define WEB_MY_WEB_SERVER_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

#include "web_code/web/web_interface.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class to extend the interface
 *
 * Extends and uses the web interface
 * Handles the updating of the buses and routes
 */
class MyWebServer : public WebInterface {
 public:
    /**
     * @brief Constructor
     */
    MyWebServer();
    /**
     * @brief Destructor
     */
    ~MyWebServer() {}

    /**
     * @brief Updates the routes using the passed in route data
     *
     * Updates each route as needed
     *
     * @param[in] route route data that needs updating
     */
    void UpdateRoute(const RouteData& route, bool deleted = false) override;
    /**
     * @brief Updates the buses using the passed in bus data
     *
     * Updates each bus as needed
     *
     * @param[in] bus bus data that needs updating
     */
    void UpdateBus(const BusData& bus, bool deleted = false) override;

    std::vector<RouteData> routes;
    std::vector<BusData> busses;
};

#endif  // WEB_MY_WEB_SERVER_H_
