/**
 * @file gold_bus_deco.cc
 *
 * @copyright 2020 Anthony Ross-Sapienza, All rights reserved.
 */

#include "src/gold_bus_deco.h"

void GoldBusDecorator::SetColor(Color c) {
  // Check if c is 0
  // If it is, assign the gold color to it
    if (c.red == 0) {
      c = Color(255, 204, 51, 100);  // Gopher Gold!
    }
    // Pass c up the chain
    bus_deco_->SetColor(c);
}
