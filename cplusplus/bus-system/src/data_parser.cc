/**
 * @file data_parser.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#include "src/data_parser.h"

std::vector<std::string> DataParser::ParseData(std::stringstream &in_data) {
    // Create strings to hold each piece of information
    std::string name;
    std::string dest_speed;
    std::string totwait_dist;
    std::string stopwait_pass;
    std::string buswait_totpass;
    // A waste string to through out irrelevant information
    std::string waste;
    in_data >> waste >> name >> waste >> dest_speed >> waste >> totwait_dist
            >> waste >> stopwait_pass >> waste >> buswait_totpass;
    // Create a string vector to hold the information
    std::vector<std::string> info;
    info.push_back(name);
    info.push_back(dest_speed);
    info.push_back(totwait_dist);
    info.push_back(stopwait_pass);
    info.push_back(buswait_totpass);
    return info;
}
