/**
 * @file bus_factory.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#include <vector>
#include <random>
#include <string>

#include "src/bus_factory.h"

// BusFactory constructor
// Initaliazes strategy_ to appropriate strategy
BusFactory::BusFactory(Route * outbound, Route * inbound, double speed) {
    outbound_ = outbound;
    inbound_ = inbound;
    speed_ = speed;
    strategy_ = new OvernightStrategy();
    strategy_ = PickStrategy();
}

// Generate a new bus using the strategy set up
// The Strategy class handles all the information needed to pick which bus
// Then use bus_type to generate and return appropriate size bus
Bus * BusFactory::Generate(std::string name) {
    // Technically, the strategy should be confirmed each time a new bus is
    // created. However, for this simulation, this is actually unnecessary.
    // delete strategy_;
    // strategy_ = PickStrategy();
    int b = strategy_->PickBus();
    if (b == 1) {
      return new SmallBus(name, outbound_, inbound_, speed_);
    } else if (b == 2) {
      return new RegularBus(name, outbound_, inbound_, speed_);
    } else {
      return new LargeBus(name, outbound_, inbound_, speed_);
    }
}

void BusFactory::UpdateRoutes(Route * out, Route * in) {
    outbound_ = out;
    inbound_ = in;
}

// Use current strategy to get the time
// Change strategy to reflect current time
Strategy * BusFactory::PickStrategy() {
    int hour = strategy_->GetTime();
    if (hour >= 6 && hour < 8) {
        return new MorningStrategy();
    } else if (hour >= 8 && hour < 15) {
        return new AfternoonStrategy();
    } else if (hour >= 15 && hour < 20) {
        return new EveningStrategy();
    } else {
        return new OvernightStrategy();
    }
}
