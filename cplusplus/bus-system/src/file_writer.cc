/**
 * @file file_writer.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */
#include "src/file_writer.h"

FileWriter * FileWriter::writer = 0;

FileWriter * FileWriter::GetWriter() {
    if (!writer) {
        writer = new FileWriter;
    }
    return writer;
}

void FileWriter::WriteToFile(std::string filename,
                             std::vector<std::string> sout) {
    // Create an ofstream object and open the appropriate file in append mode
    std::ofstream printer;
    printer.open(filename, std::ofstream::app);

    // Iterate through the string vector, adding each element to the file
    // Separate each value with a comma and start a new line after finishing
    // End result is a new line of comma separated values of appropriate info
    for (std::vector<std::string>::iterator it = sout.begin();
         it != sout.end(); it++) {
        printer << (*it);
        if (std::next(it) != sout.end()) {
            printer << ',';
        }
    }
    printer << '\n';

    printer.close();
}
