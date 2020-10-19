/**
 * @file maroon_bus_deco.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#include "src/maroon_bus_deco.h"

void MaroonBusDecorator::SetColor(Color c) {
    // Check if c is 0
    // If it is, assign the maroon color to it
    if (c.red == 0) {
      c = Color(122, 0, 25, 100);  // Gopher Gold!
    }
    // Pass c up the chain
    bus_deco_->SetColor(c);
}
