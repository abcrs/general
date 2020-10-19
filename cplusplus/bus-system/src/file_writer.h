/**
 * @file file_writer.h
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#ifndef SRC_FILE_WRITER_H_
#define SRC_FILE_WRITER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class to write data to files
 *
 * Singleton class, only one instance allowed
 * Other classes obtain data, pass data and filename to Singleton
 */
class FileWriter {
 public:
    /**
     * @brief Returns the single instance of the FileWriter
     *
     * If no instance of the FileWriter object has been created, create one
     * Otherwise return the already created instance
     *
     * @return The single instance of FileWriter
     */
    FileWriter * GetWriter();

    /**
     * @brief Add to file
     *
     * Take passed in filename and append information contained in the
     * passed in string vector, separated by commas
     */
    void WriteToFile(std::string filename, std::vector<std::string> sout);

 private:
    /**
     * @brief Private FileWriter constructer
     *
     * Private constructor so it can not be created outside the class
     */
    // FileWriter();
    static FileWriter * writer;  // Static private instance
};

#endif  // SRC_FILE_WRITER_H_
