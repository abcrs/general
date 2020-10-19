/**
 * @file local_simulator.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <list>
#include <vector>

#include "src/r2_local_simulator.h"

bool r2LocalSimulator::Start() {
  simulation_time_elapsed_ = 0;  // init, but also allows restart

  // int num_round_trips = 10;
  int num_round_trips = 1;
  for (int i = 0; i < num_round_trips; i++) {
    time_since_last_bus_generation_.push_back(0);
  }

  Stop ** CC_NB_stops = new Stop *[8];
  Stop ** CC_SB_stops = new Stop *[9];
  std::list<Stop *> CC_NB_stops_list;
  std::list<Stop *> CC_SB_stops_list;

  // Staticly defined objects get destroyed at end of Start()!
  // Must be dynamic...

  // CC Northbound stops
  Stop * stop_CC_NB_1 = new Stop(0, 44.978470, -93.235262);
  Stop * stop_CC_NB_2 = new Stop(1, 44.980284, -93.233980);
  Stop * stop_CC_NB_3 = new Stop(2, 44.983689, -93.231311);
  Stop * stop_CC_NB_4 = new Stop(3, 44.987662, -93.230257);
  Stop * stop_CC_NB_5 = new Stop(4, 44.987756, -93.227085);
  Stop * stop_CC_NB_6 = new Stop(5, 44.991818, -93.226988);

  // CC Southbound stops
  Stop * stop_CC_SB_1 = new Stop(6, 44.991636, -93.227348);
  Stop * stop_CC_SB_2 = new Stop(7, 44.987911, -93.227035);
  Stop * stop_CC_SB_3 = new Stop(8, 44.987528, -93.230487);
  Stop * stop_CC_SB_4 = new Stop(9, 44.983975, -93.231301);
  Stop * stop_CC_SB_5 = new Stop(10, 44.980187, -93.234312);
  Stop * stop_CC_SB_6 = new Stop(11, 44.978199, -93.236085);

  CC_NB_stops_list.push_back(stop_CC_NB_1);
  CC_NB_stops[0] = stop_CC_NB_1;
  CC_NB_stops_list.push_back(stop_CC_NB_2);
  CC_NB_stops[1] = stop_CC_NB_2;
  CC_NB_stops_list.push_back(stop_CC_NB_3);
  CC_NB_stops[2] = stop_CC_NB_3;
  CC_NB_stops_list.push_back(stop_CC_NB_4);
  CC_NB_stops[3] = stop_CC_NB_4;
  CC_NB_stops_list.push_back(stop_CC_NB_5);
  CC_NB_stops[4] = stop_CC_NB_5;
  CC_NB_stops_list.push_back(stop_CC_NB_6);
  CC_NB_stops[5] = stop_CC_NB_6;

  CC_SB_stops_list.push_back(stop_CC_SB_1);
  CC_SB_stops[0] = stop_CC_SB_1;
  CC_SB_stops_list.push_back(stop_CC_SB_2);
  CC_SB_stops[1] = stop_CC_SB_2;
  CC_SB_stops_list.push_back(stop_CC_SB_3);
  CC_SB_stops[2] = stop_CC_SB_3;
  CC_SB_stops_list.push_back(stop_CC_SB_4);
  CC_SB_stops[3] = stop_CC_SB_4;
  CC_SB_stops_list.push_back(stop_CC_SB_5);
  CC_SB_stops[4] = stop_CC_SB_5;
  CC_SB_stops_list.push_back(stop_CC_SB_6);
  CC_SB_stops[5] = stop_CC_SB_6;

  double * CC_NB_distances = new double[7];
  double * CC_SB_distances = new double[8];
  CC_NB_distances[0] = 4;
  CC_NB_distances[1] = 4;
  CC_NB_distances[2] = 2;
  CC_NB_distances[3] = 19;
  CC_NB_distances[4] = 1;
  CC_NB_distances[5] = 1;

  CC_SB_distances[0] = 2;
  CC_SB_distances[1] = 1;
  CC_SB_distances[2] = 2;
  CC_SB_distances[3] = 19;
  CC_SB_distances[4] = 3;
  CC_SB_distances[5] = 3;


  std::list<double> CC_NB_probs;    //  realistic .15, .3, .025, .05, .05, 0
  CC_NB_probs.push_back(.15);
  CC_NB_probs.push_back(.3);
  CC_NB_probs.push_back(.025);
  CC_NB_probs.push_back(.05);
  CC_NB_probs.push_back(.05);
  CC_NB_probs.push_back(0);
  //  If so, we may want to reduce the length of probs to_char_type
  //  remove possibility of generating passengers with nowhere to go

  std::list<double> CC_SB_probs;    //  realistic .35, .05, .01, .01, .2, 0
  CC_SB_probs.push_back(.35);
  CC_SB_probs.push_back(.05);
  CC_SB_probs.push_back(.01);
  CC_SB_probs.push_back(.01);
  CC_SB_probs.push_back(.025);
  CC_SB_probs.push_back(0);

  //  Staticly defined objects get destroyed at end of Start()!
  //  Must be dynamic...
  //  RandomPassengerGenerator CC_NB_generator(CC_NB_probs, CC_NB_stops_list);
  //  RandomPassengerGenerator CC_SB_generator(CC_SB_probs, CC_SB_stops_list);

  RtestPassengerGenerator * CC_NB_generator =
        new RtestPassengerGenerator (CC_NB_probs, CC_NB_stops_list);
  RtestPassengerGenerator * CC_SB_generator =
        new RtestPassengerGenerator (CC_SB_probs, CC_SB_stops_list);

  //  Test to ensure generators are working
  //  Helpful for dNBugging
  //  CC_NB_generator.GeneratePassengers();
  //  CC_SB_generator.GeneratePassengers();

  //  Again, MUST be dynamic...
  //  Route CC_NB("Campus Connector - Eastbound", CC_NB_stops,
  //              CC_NB_distances, 8, &CC_NB_generator);
  //  Route CC_SB("Campus Connector - Westbound", CC_SB_stops,
  //              CC_SB_distances, 9, &CC_SB_generator);

  Route * CC_NB = new Route("Quarry Run - Northbound",
                            CC_NB_stops, CC_NB_distances, 6, CC_NB_generator);
  Route * CC_SB = new Route("Quarry Run - Southbound",
                            CC_SB_stops, CC_SB_distances, 6, CC_SB_generator);

  prototype_routes_.push_back(CC_NB);
  prototype_routes_.push_back(CC_SB);

  prototype_routes_[0]->Report(std::cout);
  prototype_routes_[1]->Report(std::cout);

  bus_counters_.push_back(10000);

  //  This will eventually be replaced by configuration/command line argument
  bus_start_timings_.push_back(10);

  //  Do we want a bus on start? Or let the update handle this?
  //  active_buses_.push_back(new Bus(std::to_string(bus_counters_[0]),
  //    prototype_routes[0].Clone(), prototype_routes[1].Clone(), 60, 1));
  //  bus_counters_[0]++;

  return true;
}

bool r2LocalSimulator::Update() {
  // increase time
  simulation_time_elapsed_++;
  std::cout << "~~~~~~~~~~~~~ The time is now " << simulation_time_elapsed_;
  std::cout << " ~~~~~~~~~~~~~" << std::endl;

  // various route-indexed list iterators
  std::vector<int>::iterator bus_gen_timing_iter = bus_start_timings_.begin();
  std::vector<int>::iterator bus_counter_iter = bus_counters_.begin();
  std::vector<Route *>::iterator prototype_route_iter =
                                                     prototype_routes_.begin();

  // increase each time since last bus
  // various iterators parallel the time_since_last iterator
  for (std::vector<int>::iterator it = time_since_last_bus_generation_.begin();
      it != time_since_last_bus_generation_.end();
      it++, bus_gen_timing_iter++, bus_counter_iter++) {
    (*it)++;

    // if time since last [index] == bus gen timing[index]
    if (0 >= (*bus_gen_timing_iter)) {
      // create a new bus! routes are:
      // prototype_routes_[index * 2] & prototype_routes_[index * 2 + 1]
      Route * outbound = (*prototype_route_iter);
      prototype_route_iter++;
      Route * inbound = (*prototype_route_iter);
      prototype_route_iter++;

      active_buses_.push_back(new Bus(std::to_string((*bus_counter_iter)),
                                  outbound->Clone(), inbound->Clone(), 60, 1));
      (*bus_counter_iter)++;
      (*bus_gen_timing_iter) = 10;
    } else {
      prototype_route_iter++;
      prototype_route_iter++;
      (*bus_gen_timing_iter)--;
    }
  }

  // for each bus
  for (std::list<Bus *>::iterator bus_iter = active_buses_.begin();
      bus_iter != active_buses_.end(); bus_iter++) {
    // update bus
    (*bus_iter)->Update();
    // bus report
    (*bus_iter)->Report(std::cout);

    //  REQUIRES USE OF IsTripComplete, which was not required
    //  Buses which are "done" will just keep having Update() called
    //    Students MAY need to deal with this, not sure yet...
    //  remove bus if trip is complete
    //  if ((*bus_iter)->IsTripComplete()) {
    //    bus_iter = active_buses_.erase(bus_iter);
    //    bus_iter--;
    //  }
  }

  // for each stop
  for (std::vector<Route *>::iterator route_iter = prototype_routes_.begin();
      route_iter != prototype_routes_.end(); route_iter++) {
    // update stop
    (*route_iter)->Update();
    (*route_iter)->Report(std::cout);
  }

  return true;
}
