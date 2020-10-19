/**
 * @file alpha_bus_deco.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#include "src/alpha_bus_deco.h"

void AlphaBusDecorator::SetAlpha(int a) {
    int pass = static_cast<int>(bus_deco_->GetNumPassengers());
    // Pick the color intensity on a range from 105 - 255
    // Intensity depends on how full bus is
    // Intensity starts at 105 for 0 passengers, and goes up by 25 for each
    // Passenger added, up to 8 passengers and a max intensity of 255
    a = 255;
    if (pass < 9) {
        a -= (8 - pass) * 25;
    }
    // Finally update the new color using this intensity
    bus_deco_->SetAlpha(a);
}
