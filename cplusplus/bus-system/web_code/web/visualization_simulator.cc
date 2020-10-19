/**
 * @file bus.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 **/

#include <string>

#include "visualization_simulator.h"  // NOLINT
#include "src/ibus.h"
#include "src/route.h"
#include "src/data_structs.h"

VisualizationSimulator::VisualizationSimulator(WebInterface* webI,
                                               ConfigManager* configM) {
    webInterface_ = webI;
    configManager_ = configM;
}

VisualizationSimulator::~VisualizationSimulator() {
}

void VisualizationSimulator::Start(const std::vector<int>& busStartTimings,
                                   const int& numTimeSteps) {
    busStartTimings_ = busStartTimings;
    numTimeSteps_ = numTimeSteps;

    // Set up the column headers for both the passenger and bus .csv files
    std::ofstream bus_intro;
    std::ofstream pass_intro;
    bus_intro.open(bus_data_file_);
    bus_intro << "Name" << "," << "Speed" << "," << "Distance to Next Stop"
              << "," << "Current Passengers" << "," << "Total Passengers\n";
    pass_intro.open(pass_data_file_);
    pass_intro << "Name" << "," << "Destination" << "," << "Total Wait"
               << "," << "Wait at Stop" << "," << "Time on Bus\n";
    bus_intro.close();
    pass_intro.close();

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);

        prototypeRoutes_[i]->UpdateRouteData();
        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
    }
    Route * outbound = prototypeRoutes_[0];
    Route * inbound = prototypeRoutes_[1];
    busFactory_ = new BusFactory(outbound->Clone(), inbound->Clone(), 1);
}

void VisualizationSimulator::End() {
    // Iterate through the remaining buses to print all of their data
    // to the .csv file, despite their runs not finishing
    for (int i = 0; i < static_cast<int>(busses_.size()); i++) {
      std::stringstream bus_string;
      busses_[i]->Report(bus_string);
      std::vector<std::string> data_bus = DataParser::ParseData(bus_string);
      bus_data_writer_->WriteToFile(bus_data_file_, data_bus);
    }
}

void VisualizationSimulator::Pause() {
    paused_ = !paused_;
}

void VisualizationSimulator::Update() {
    if (!paused_) {
        simulationTimeElapsed_++;

        std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
        std::cout << "~~~~~~~~~~" << std::endl;

        std::cout << "~~~~~~~~~~ Generating new busses if needed ";
        std::cout << "~~~~~~~~~~" << std::endl;

        // Check if we need to generate new busses
        for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
            // Check if we need to make a new bus
            if (0 >= timeSinceLastBus_[i]) {
                Route * outbound = prototypeRoutes_[2 * i];
                Route * inbound = prototypeRoutes_[2 * i + 1];

                busFactory_->UpdateRoutes(outbound->Clone(), inbound->Clone());
                Bus * n_bus = busFactory_->Generate(std::to_string(busId));
                BusDecorator * d_bus = new BusDecorator(n_bus);
                MaroonBusDecorator * m_bus = new MaroonBusDecorator(d_bus);
                m_bus->SetColor(Color(0, 0, 0));
                busses_.push_back(m_bus);
                busId++;

                timeSinceLastBus_[i] = busStartTimings_[i];
            } else {
                timeSinceLastBus_[i]--;
            }
        }

        std::cout << "~~~~~~~~~ Updating busses ";
        std::cout << "~~~~~~~~~" << std::endl;

        // Update busses
        for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
            busses_[i]->Update();
            if (busses_[i]->OutRouteDone() == true) {
                busses_[i] = new GoldBusDecorator(busses_[i]);
                busses_[i]->SetColor(Color(0, 0, 0));
            }
            busses_[i] = new AlphaBusDecorator(busses_[i]);
            busses_[i]->SetAlpha(0);

            if (busses_[i]->IsTripComplete()) {
                // If bus has completed run, print data to the .csv file
                std::stringstream bus_string;
                busses_[i]->Report(bus_string);
                std::vector<std::string> data_bus =
                                            DataParser::ParseData(bus_string);
                bus_data_writer_->WriteToFile(bus_data_file_, data_bus);
                webInterface_->UpdateBus(busses_[i]->GetBusData(), true);
                busses_.erase(busses_.begin() + i);
                continue;
            }

            webInterface_->UpdateBus(busses_[i]->GetBusData());

            busses_[i]->Report(std::cout);
        }

        std::cout << "~~~~~~~~~ Updating routes ";
        std::cout << "~~~~~~~~~" << std::endl;
        // Update routes
        for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
            prototypeRoutes_[i]->Update();

            webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());

            prototypeRoutes_[i]->Report(std::cout);
        }
    }
}

// Iterate through the busses_ list and call ClearObservers() on each object
// Then iterate through the prototypeRoutes_ list and clear stops of observers
void VisualizationSimulator::ClearListeners() {
    for (std::vector<IBus *>::iterator iter = busses_.begin();
         iter != busses_.end(); ++iter) {
        (*iter)->ClearObservers();
    }
    for (std::vector<Route *>::iterator rit = prototypeRoutes_.begin();
         rit != prototypeRoutes_.end(); ++rit) {
        std::list<Stop *> stops = (*rit)->GetStops();
        for (std::list<Stop *>::iterator sit = stops.begin();
             sit != stops.end(); ++sit) {
            (*sit)->ClearObservers();
        }
    }
}

// Iterate through busses_ list to see if any match the passed in id
// If yes, register the passed in observer to that bus object
void VisualizationSimulator::AddBusListener(std::string * id,
                                         IObserver * observer) {
    std::string check_id = *id;
    for (std::vector<IBus *>::iterator iter = busses_.begin();
         iter != busses_.end(); ++iter) {
        if ((*iter)->GetName().compare(check_id) == 0) {
            (*iter)->RegisterObserver(observer);
        }
    }
}

// Iterate through the prototypeRoutes_ list, checking each stop to see if
// any match the passed in string id (should always be true)
// If yes, add an observer to that stop
void VisualizationSimulator::AddStopListener(std::string * id,
                                         IObserver * observer) {
    int check_id = std::stoi(*id);
    for (std::vector<Route *>::iterator rit = prototypeRoutes_.begin();
         rit != prototypeRoutes_.end(); ++rit) {
        std::list<Stop *> stops = (*rit)->GetStops();
        for (std::list<Stop *>::iterator sit = stops.begin();
             sit != stops.end(); ++sit) {
            if ((*sit)->GetId() == check_id) {
                (*sit)->RegisterObserver(observer);
            }
        }
    }
}
