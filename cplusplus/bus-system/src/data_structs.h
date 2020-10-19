/**
 * @file data_structs.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */


#ifndef SRC_DATA_STRUCTS_H_
#define SRC_DATA_STRUCTS_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>

/**
 * A structure to represent x,y position
 */
struct Position {
    /**
     * @brief Constructor creating a posisiton object
     *
     * Object contains x and y value
     */
    Position(float xx, float yy): x(xx), y(yy) { }
    /**
     * @brief Default Constructor
     *
     * Values initialized to 0
     */
    Position() : x(0), y(0) {}
    /*@{*/
    float x;
    float y;
    /*@}*/
};

/**
 * A structure to represent r,g,b,a color
 */
struct Color {
    /**
     * @brief Color constructor
     *
     * Will set default color to black
     */
    explicit Color(int r = 0, int g = 0, int b = 0, int a = 255):
        red(r), green(g), blue(b), alpha(a) { }
    /*@{*/
    int red;
    int green;
    int blue;
    int alpha;
    /*@}*/
};

/**
 * A structure to represent a snapshot of bus data
 */
struct BusData {
    /**
     * @brief BusData constructor
     *
     * Object that holds bus name, position, passengers, capapcity, and color
     * Assigns all passed in values to relevant fields
     */
    BusData(std::string idd, Color ccolor, Position pos, int n_pass, int cap):
        id(idd), position(pos), num_passengers(n_pass),
        capacity(cap), color(ccolor) {}
    /**
     * @brief BusData default constructor
     *
     * Object that holds bus name, position, passengers, capapcity, and color
     */
    BusData():
        id(""), position(Position()), num_passengers(0), capacity(0), color() {}
    /*@{*/
    std::string id;
    Position position;
    int num_passengers;
    int capacity;
    Color color;
    /*@}*/
};

/**
 * A structure to represent a stop data
 */
struct StopData {
    /**
     * @brief StopData constructor
     *
     * Object that holds stop id, position, and the people waiting at the stop
     */
    StopData(std::string idd, Position pos , int n_peeps):
             id(idd), position(pos), num_people(n_peeps) {}
    /**
     * @brief StopData default constructor
     *
     * Initializes all values to 0/blank
     */
    StopData() : id(""), position(Position()), num_people(0) {}
    /*@{*/
    std::string id;
    Position position;
    int num_people;
    /*@{*/
};

/**
 * A structure to represent a route data
 */
struct RouteData {
    /**
     * @brief RouteData constructor
     *
     * Initializes values to relevant fields
     */
    explicit RouteData(std::string idd):
                       id(idd), stops(std::vector<StopData>(0)) {}
    /**
     * @brief RouteData default constructor
     *
     * Initializes all values to 0/blank
     */
    RouteData() : id(""), stops(std::vector<StopData>(0)) {}
    /*@{*/
    std::string id;
    std::vector<StopData> stops;
    /*@{*/
};

#endif  // SRC_DATA_STRUCTS_H_
