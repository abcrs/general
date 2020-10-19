/**
 * @file passenger_unloader.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <string>
#include <vector>

#include "src/passenger_unloader.h"

int PassengerUnloader::UnloadPassengers(std::list<Passenger *> * passengers,
                                        Stop * current_stop) {
  // TODO(wendt): may need to do end-of-life here
  // instead of in Passenger or Simulator
  int passengers_unloaded = 0;
  std::stringstream pass_string;
  for (std::list<Passenger *>::iterator it = passengers->begin();
      it != passengers->end();
      it++) {
    if ((*it)->GetDestination() == current_stop->GetId()) {
      // could be used to inform scheduler of end-of-life?
      // This could be a destructor issue as well.
      // *it->FinalUpdate();
      (*it)->Report(pass_string);
      std::vector<std::string> data_pass = DataParser::ParseData(pass_string);
      pass_data_writer_->WriteToFile(pass_data_file_, data_pass);
      it = passengers->erase(it);
      // getting seg faults, probably due to reference deleted objects
      // here
      it--;
      passengers_unloaded++;
    }
  }

  return passengers_unloaded;
}
