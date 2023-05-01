/**
 * @file recipes.hpp
 * @brief Contains recipes for the beverages. This file is meant to be inline-included before the
 *        recipes can be used. Expects a DISPENSER macro that is defined as a ::dispenser class pointer.
 */

// 6000ms - 200ml from 1 tank
// 3000ms - 200ml from 2 tanks
// 2300ms - 200ml from 3 tanks
// 1950ms - 200ml from 4 tanks

namespace recipes {

void drink1() {
  DISPENSER->dispense(pump_location::left, 6000);
}

void drink2() {
  DISPENSER->dispense(pump_location::mid_left, 6000);
}

void drink3() {
  DISPENSER->enable(pump_location::left);
  DISPENSER->enable(pump_location::mid_left);
  delay(3000);
  DISPENSER->disable(pump_location::left);
  DISPENSER->disable(pump_location::mid_left);
}

void drink4() {
  DISPENSER->enable(pump_location::left);
  DISPENSER->enable(pump_location::mid_left);
  DISPENSER->enable(pump_location::mid_right);
  delay(2300);
  DISPENSER->disable(pump_location::left);
  DISPENSER->disable(pump_location::mid_left);
  DISPENSER->disable(pump_location::mid_right);
}

void drink5() {
  DISPENSER->enable(pump_location::left);
  DISPENSER->enable(pump_location::mid_left);
  DISPENSER->enable(pump_location::mid_right);
  DISPENSER->enable(pump_location::right);
  delay(1950);
  DISPENSER->disable(pump_location::left);
  DISPENSER->disable(pump_location::mid_left);
  DISPENSER->disable(pump_location::mid_right);
  DISPENSER->disable(pump_location::right);
}
}