#include "Arduino.h"
#include "Buttons.h"

Buttons::Buttons() {

  pinMode(PIN_BUTTON_LADDER, INPUT);

  // initialize values to sensible defaults
  _record_button_press(NO_BUTTON);
}


void Buttons::_record_button_press(int button) {
  _last_button_pressed = button;
  _time_button_pressed = millis();
}


int Buttons::get_button_press() {
  int button = _get_current_button();

  if (button != _last_button_pressed) {
    _record_button_press(button);

    Serial.print("current button: ");
    Serial.print(button);
    Serial.print(" ");
    Serial.println(_time_button_pressed);

    return button;
  }

  // If a button change was not detected then return that no button is being
  // pressed.
  return NO_BUTTON;

}

int Buttons::_get_current_button() {
  int button_pin_value = analogRead(PIN_BUTTON_LADDER);

  // Serial.print("button_pin_value value: ");
  // Serial.println(button_pin_value);

  if (button_pin_value >= BUTTON_MODE_MIN_VALUE && button_pin_value <= BUTTON_MODE_MAX_VALUE) {
    return BUTTON_MODE;
  }
  else if (button_pin_value >= BUTTON_PLUS_MIN_VALUE && button_pin_value <= BUTTON_PLUS_MAX_VALUE) {
    return BUTTON_PLUS;
  }
  else if (button_pin_value >= BUTTON_MINUS_MIN_VALUE && button_pin_value <= BUTTON_MINUS_MAX_VALUE) {
    return BUTTON_MINUS;
  }
  else if (button_pin_value >= BUTTON_RESTART_MIN_VALUE && button_pin_value <= BUTTON_RESTART_MAX_VALUE) {
    return BUTTON_RESTART;
  }
  else {
    return NO_BUTTON;
  }
}
