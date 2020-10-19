/**
 * @file bus.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/bus.h"

Bus::Bus(std::string name, Route * out, Route * in, int capacity,
         double speed, std::string type) {
    name_ = name;
    outgoing_route_ = out;
    incoming_route_ = in;
    outgoing_route_done_ = false;
    total_passengers_ = 0;
    passenger_max_capacity_ = capacity;
    speed_ = speed;
    type_ = type;
    distance_remaining_ = 0;
    next_stop_ = out->GetDestinationStop();
    unloader_ = new PassengerUnloader;
    loader_ = new PassengerLoader;
    bus_data_.color = Color(0, 0, 0, 255);
}

bool Bus::IsTripComplete() {
  bool is_complete = false;

  // short-circuit: outgoing has to be completed first
  if (outgoing_route_done_ && incoming_route_->IsAtEnd()) {
    is_complete = true;
  }

  return is_complete;
}

bool Bus::LoadPassenger(Passenger * new_passenger) {
  bool added_passenger = false;
  if (loader_->LoadPassenger(new_passenger, passenger_max_capacity_,
                             &passengers_) == true) {
    added_passenger = true;
    // revenue_ += 0; //No revenue tracking at this time.
  }
  return added_passenger;
}

bool Bus::Move() {
  // update all passengers FIRST
  // new passengers will get "updated" when getting on the bus
  for (std::list<Passenger *>::iterator it = passengers_.begin();
                                  it != passengers_.end(); it++) {
    (*it)->Update();
  }

  bool did_move = true;

  // travel happens in all cases
  // neg distance indicates ready to unload/load
  if (speed_ > 0) {
    distance_remaining_ -= speed_;
  } else {
    did_move = false;
  }
  int passengers_handled = 0;  // counts those on or off bus at this location

  // if there's no more distance
  // (OFF BY ONE ERROR ISSUE - do we unload if exactly zero after a move?
  // or only if there was time remaining?)

  if (distance_remaining_ <= 0) {
    did_move = false;
    // Determine which route we are on
    Route * current_route = outgoing_route_;
    if (outgoing_route_done_) {
      current_route = incoming_route_;
      if (!incoming_route_->IsAtEnd()) {
        // Only get here if we are on our incoming route
        passengers_handled += UnloadPassengers();  // unload
        int temp = next_stop_->LoadPassengers(this);  // load
        total_passengers_ += temp;
        passengers_handled += temp;

        // if any passengers on or off,
        // all distance to next stop is left
        // but, if we didn't handle any passengers here,
        // any negative will affect the distance remaining
        // (see addition below)
        if (passengers_handled != 0) {
          distance_remaining_ = 0;
          did_move = true;  // We move if we have gotten passengers?
        } else {
          std::cout << "Bus " << name_ << " skipped stop "
                    << current_route->GetDestinationStop()->GetId()
                    << "." << std::endl;
        }
        current_route->ToNextStop();
        next_stop_ = current_route->GetDestinationStop();
        distance_remaining_ += current_route->GetNextStopDistance();
        return did_move;
      } else {
        speed_ = 0;
        distance_remaining_ = 999;
        return did_move;
      }
    }

    // Only get here if we are on outgoing route
    passengers_handled += UnloadPassengers();  // unload
    int temp = next_stop_->LoadPassengers(this);  // load
    total_passengers_ += temp;
    passengers_handled += temp;

    // if any passengers on or off, all distance to next stop is left
    // but, if we didn't handle any passengers here, any negative will
    // affect the distance remaining (see addition below)
    if (passengers_handled != 0) {
      distance_remaining_ = 0;
      did_move = true;
    } else {
      std::cout << "Bus " << name_ << " skipped stop "
                << current_route->GetDestinationStop()->GetId()
                << "." << std::endl;
    }

    current_route->ToNextStop();

    // If we have incremented past the end of the outgoing route, set our
    // next stop to actually be the first stpo in incoming
    if (current_route->IsAtEnd()) {
      outgoing_route_done_ = true;
      next_stop_ = incoming_route_->GetDestinationStop();
      distance_remaining_ += incoming_route_->GetNextStopDistance();
    } else {
      next_stop_ = current_route->GetDestinationStop();

      // adding here in case negative time still remains
      // // (see passengers_handled above)
      distance_remaining_ += current_route->GetNextStopDistance();
    }
  }
  return did_move;
}

// bool Refuel() {
// //This may become more complex in the future
// fuel_ = max_fuel_;
// }

void Bus::Update() {  // using common Update format
  Move();
  UpdateBusData();
  NotifyBusObservers(&bus_data_);
}

void Bus::Report(std::ostream& out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance-to-next-stop: " << distance_remaining_ << std::endl;
  out << "\tCurrent-Passengers: " << passengers_.size() << std::endl;
  out << "\tTotal-Passengers: " << total_passengers_ << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
                                        it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

int Bus::UnloadPassengers() {
  int passengers_unloaded = 0;
  unloader_->UnloadPassengers(&passengers_, next_stop_);
  return passengers_unloaded;
}

void Bus::UpdateBusData() {
    bus_data_.id = name_;
    // Get the correct route and early exit
    Route * current_route = outgoing_route_;
    // Create a color baseline that can be changed later on
    if (outgoing_route_->IsAtEnd()) {
        if (incoming_route_->IsAtEnd()) { return; }
        current_route = incoming_route_;
    }

    Stop * prevStop = current_route->PrevStop();
    Stop * nextStop = current_route->GetDestinationStop();

    double distanceBetween = current_route->GetNextStopDistance();
    double ratio;

    // Need to check if we are at the first stop
    if (distanceBetween - 0.00001 < 0) {
        ratio = 1;
    } else {
        ratio = distance_remaining_ / distanceBetween;
        if (ratio < 0) {
            ratio = 0;
            distance_remaining_ = 0;
        }
    }

    // This ratio shows us how far from the previous stop are we in a ratio
    // from 0 to 1
    Position p;
    p.x = (nextStop->GetLongitude()*(1-ratio)+prevStop->GetLongitude()*ratio);
    p.y = (nextStop->GetLatitude()*(1-ratio)+prevStop->GetLatitude()*ratio);
    bus_data_.position = p;

    bus_data_.num_passengers = static_cast<int>(passengers_.size());
    bus_data_.capacity = passenger_max_capacity_;
}

BusData Bus::GetBusData() const {
    return bus_data_;
}