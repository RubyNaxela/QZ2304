/**
 * @file button_panel.hpp
 * @brief Contains the class that represents a QZ2304B button panel.
 */

#ifndef QZ2304_BUTTON_PANEL
#define QZ2304_BUTTON_PANEL

#include "io.hpp"
#include "utility.hpp"

/**
 * An auxiliary enumeration listing available buttons.
 */
enum button {
  btn1 = 0, ///< The leftmost button (button 1)
  btn2 = 1, ///< The mid-left button (button 2)
  btn3 = 2, ///< The middle button (button 3)
  btn4 = 3, ///< The mid-right button (button 4)
  btn5 = 4  ///< The rightmost button (button 5)
};

/**
 * Represents the QZ2304B button panel. The panel can be interfaced through state polling. In order to perform
 * actions in response to the inputs, a callback should be specified using the ::set_button_callback() method.
 * The ::poll_state() method should be called repeatedly so that the callback can be executed in response to inputs.
 * @tparam Mode  if digital pins are used, this must be input_mode::digital. By analogy, if analog pins are used, Mode must be input_mode::analog.
 */
template<input_mode Mode>
class button_panel {

  digital_input_pin<Mode>* inputs[5];     // Pointers to the button objects
  void (*callback)(button btn) = nullptr; // Pointer to the input callback

  // Returns the index of currently active button, or 255 if none is active.
  uint8_t active_button() const {
    if (callback != nullptr)
      for (uint8_t i = 0; i < 5; i++)
        if (inputs[i]->is_active()) return i;
    return NONE;
  }

  typedef digital_input_pin<Mode> btn_pin;

public:

  /**
   * Creates and initializes a button panel object.
   * @param in1 the leftmost button (button 1) pin
   * @param in2 the mid-left button (button 2) pin
   * @param in3 the middle button (button 3) pin
   * @param in4 the mid-right button (button 4) pin
   * @param in5 the rightmost button (button 5) pin
   */
  button_panel(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t in5)
    : inputs{ new btn_pin(in1), new btn_pin(in2), new btn_pin(in3), new btn_pin(in4), new btn_pin(in5) } {}

  /**
   * Releases the resources allocated for the input pin objects.
   */
  ~button_panel() {
    for (uint8_t i = 0; i < 5; i++) delete inputs[i];
  }

  /**
   * Sets the callback to be executed whenever any of the buttons is pressed. May be later reassigned.
   * @param callback  the callback for button inputs, may be `nullptr`
   */
  void set_button_callback(void (*callback)(button btn)) {
    this->callback = callback;
  }

  /**
   * Polls the state of the buttons and executes the callback if any of them is pressed. Should be called repeatedly so that
   * the callback can be executed in response to inputs. If the callback has not been specified, this method does nothing.
   */
  void poll_state() const {
    if (callback != nullptr) {
      const uint8_t input = active_button();
      if (input != uint8_t(NONE)) {
        for (uint8_t i = 0; i < 4; i++) {
          delay(10);
          if (active_button() != input) return;
        }
        callback(button(input));
      }
    }
  }
};

#endif  // QZ2304_BUTTON_PANEL