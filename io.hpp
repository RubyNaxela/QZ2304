/**
 * @file io.hpp
 * @brief Contains classes for handling input and output from/to a QZ2304M board pins.
 */

#ifndef QZ2304_IO
#define QZ2304_IO

/**
 * Specifies the mode of digital input - whether a digital or an analog pin is used.
 */
enum input_mode {
  digital,  ///< Digital pin mode
  analog    ///< Analog pin mode
};

/**
 * A digital input handler for an analog or digital pin. This class provides a method to retrieve the digital state of any pin.
 * @tparam Mode  if a digital pin is used, this must be input_mode::digital. By analogy, if an analog pin is used, Mode must be input_mode::analog.
 */
template<input_mode Mode>
class digital_input_pin {

  uint8_t pin;

public:

  /**
   * Creates an output handler for the specified pin.
   * @param pin  the pin to be controlled by this handler
   */
  digital_input_pin(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT);
  }

  bool is_active() const {
    if (Mode == input_mode::digital) return digitalRead(pin);
    else if (Mode == input_mode::analog) return analogRead(pin) > 511;
    return false;
  }
};

/**
 * An output handler for a digital pin. This class provides a few methods to ease the use of QZ2304M digital outputs.
 */
class output_pin {

  uint8_t pin; // The number of the pin being controlled by this handler
  bool state;  // The current state of the pin. "true" means high voltage, "false" means low.

  // Sets the state of both the pin and the field of this object.
  void set_state(bool state) {
    digitalWrite(pin, state);
    this->state = state;
  }

public:

  /**
   * Creates an output handler for the specified pin.
   * @param pin  the pin to be controlled by this handler
   */
  output_pin(uint8_t pin) : pin(pin), state(false) {
    pinMode(pin, OUTPUT);
  }

  /**
   * Enables this pin by sending high voltage to it.
   */
  void enable() {
    set_state(true);
  }

  /**
   * Disables this pin by sending low voltage to it.
   */
  void disable() {
    set_state(false);
  }

  /**
   * Returns true if this pin is enabled (has high voltage applied) and false otherwise.
   */
  bool is_enabled() const {
    return state;
  }

  /**
   * Negates the state of this pin.
   */
  void toggle() {
    set_state(!state);
  }

  /**
   * Blinks this pin for the specified duration and waits the specified amount of time afterwards. If this pin is disabled,
   * a high voltage pulse  of the specified duration is performed. Otherwise, a low voltage pulse is performed. After that,
   * the pin is set to its previous state. This function blocks until the delay specified by post_delay ends.
   * @param duration    the duration of the pulse in milliseconds
   * @param post_delay  the time to wait after the pulse in milliseconds; default: 0
   */
  void blink(uint64_t duration, uint64_t post_delay = 0) const {
    digitalWrite(pin, !state);
    delay(duration);
    digitalWrite(pin, state);
    delay(post_delay);
  }
};

#endif  // QZ2304_IO