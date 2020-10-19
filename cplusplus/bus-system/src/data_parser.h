/**
 * @file data_parser.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#ifndef SRC_DATA_PARSER_H_
#define SRC_DATA_PARSER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <sstream>
#include <string>
#include <vector>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/*
 * @brief Class to process data from report functions
 *
 * Takes data from Report() and saves valueable information
 */
class DataParser {
 public:
    /*
     * @brief Parses from passed in ostringstream
     *
     * Parses through important data in the ostringstream
     * Discards a lot of extraneous information
     *
     * @param[in] ostringstream object holding data
     *
     * @return A string vector with important information
     */
    static std::vector<std::string> ParseData(std::stringstream &in_data);
};

#endif  // SRC_DATA_PARSER_H_
