/**
 * @file dispenser.hpp
 * @brief Contains the class that represents a beverage dispenser.
 */

#ifndef QZ2304_DISPENSER
#define QZ2304_DISPENSER

/**
 * An auxiliary enumeration listing available pumps.
 */
enum pump_location {
  left = 0,      ///< the leftmost tank pump
  mid_left = 1,  ///< the mid-left tank pump
  mid_right = 2, ///< the mid-right tank pump
  right = 3      ///< the rightmost tank pump
};

/**
 * Represents the QZ2304R and HSB-300 based beverage dispenser. Provides a few handy methods for timed control of the pumps.
 */
class dispenser {

  uint8_t pump1, pump2, pump3, pump4; // The pins of the pumps

  // Translates a pump location to its pin
  uint8_t pump_pin(pump_location pump) const {
    if (pump == left) return pump1;
    else if (pump == mid_left) return pump2;
    else if (pump == mid_right) return pump3;
    else if (pump == right) return pump4;
    else return -1;
  }

public:

  /**
   * Creates and initialzies a dispenser object.
   * @param left_pump       the leftmost pump pin
   * @param mid_left_pump   the mid-left pump pin
   * @param mid_right_pump  the mid-right pump pin
   * @param right_pump      the rightmost pump pin
   */
  dispenser(uint8_t left_pump, uint8_t mid_left_pump, uint8_t mid_right_pump, uint8_t right_pump)
    : pump1(left_pump), pump2(mid_left_pump), pump3(mid_right_pump), pump4(right_pump) {
    pinMode(pump1, OUTPUT);
    pinMode(pump2, OUTPUT);
    pinMode(pump3, OUTPUT);
    pinMode(pump4, OUTPUT);
  }

  /**
   * Enables a pump flow for the specified amount of time. This function blocks until the specified duration ends.
   * @param pump      the pump location
   * @param duration  the flow duration in milliseconds
   */
  void dispense(pump_location pump, uint16_t duration) const {
    const uint8_t pin = pump_pin(pump);
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
  }

  /**
   * Starts a pump flow.
   * @param pump  the pump location
   */
  void enable(pump_location pump) const {
    digitalWrite(pump_pin(pump), HIGH);
  }

  /**
   * Stops a pump flow.
   * @param pump  the pump location
   */
  void disable(pump_location pump) const {
    digitalWrite(pump_pin(pump), LOW);
  }
};

#endif  // QZ2304_DISPENSER