/**
 * @file config_manager.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONFIG_MANAGER_H_
#define SRC_CONFIG_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>


class Route;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manages route configuration
 *
 * Uses a .txt file to "upload" routes to system
 */
class ConfigManager {
 public:
/**
 * @brief ConfigManager constructor
 *
 * Creates a configmanager object
 */
  ConfigManager();
/**
 * @brief ConfigManager destructor
 *
 * Sets each route to null, then clears the routes vector
 */
  ~ConfigManager();
/**
 * @brief Reads .txt file
 *
 * Opens a .txt file that contains route information
 * Parses through file to fill relevant information into system
 *
 * @param[in] filename of a .txt file
 */
  void ReadConfig(const std::string filename);

/**
 * @brief Gives routes
 *
 * Gives routes that were determined from the .txt file
 *
 * @return Vector contaning route information
 */
  std::vector<Route *> GetRoutes() const { return routes; }

 private:
  std::vector<Route *> routes;
};

#endif  // SRC_CONFIG_MANAGER_H_
