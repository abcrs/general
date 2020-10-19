/**
 * @file r_local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_R2_LOCAL_SIMULATOR_H_
#define SRC_R2_LOCAL_SIMULATOR_H_

#include <string>
#include <vector>

#include "src/simulator.h"

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "src/rtest_passenger_generator.h"

class r2LocalSimulator : public Simulator {
 public:
    bool Start() override;
    bool Update() override;

 private:
    std::vector<int> bus_counters_;
    std::vector<int> bus_start_timings_;
    std::vector<int> time_since_last_bus_generation_;
    int simulation_time_elapsed_;
};

#endif  // SRC_R2_LOCAL_SIMULATOR_H_
