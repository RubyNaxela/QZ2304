#include "button_panel.hpp"
#include "dispenser.hpp"
#include "io.hpp"
#include "utility.hpp"

auto* drink_selector = new button_panel<input_mode::analog>(A1, A2, A3, A4, A5);
auto* drink_dispenser = new dispenser(5, 6, 7, 8);
auto* cup_sensor = new ultrasonic_sensor(10, 9);
auto* led_strip = new output_pin(4);
auto* signal = new output_pin(13);

#define DISPENSER drink_dispenser
#include "recipes.hpp"

void on_drink_selected(button selected) {
  if (cup_sensor->measureDistanceCm() <= 6.5) {
    if (selected == button::btn1) recipes::drink1();
    else if (selected == button::btn2) recipes::drink2();
    else if (selected == button::btn3) recipes::drink3();
    else if (selected == button::btn4) recipes::drink4();
    else if (selected == button::btn5) recipes::drink5();
  } else {
    REPEAT(2) signal->blink(60, 30);
    REPEAT(3) led_strip->blink(150, 150);
  }
}

void setup() {
  drink_selector->set_button_callback(on_drink_selected);
  led_strip->enable();
}

void loop() {
  drink_selector->poll_state();
}