#include "Arduino.h"
#include "Buttons.h"

Buttons::Buttons() {}


void Buttons::setup () {
  pinMode(PIN_BUTTON_LADDER, INPUT);

  // initialize values to sensible defaults
  _record_button_press(NO_BUTTON);
}

void Buttons::_record_button_press(int button) {
  _last_button_pressed = button;
  _time_button_pressed = millis();
  Serial.print("_record_button_press: ");
  Serial.print(button);
  Serial.print(" ");
  Serial.println(_time_button_pressed);
}


int Buttons::get_button_press() {
  int button = _get_current_button();

  // debounce the button press. When speaker in being used with tone it seems
  // to jitter the button ladder input.
  if (button != _debounce_button_identified) {
    // New button - start the debounce timeout
    _debounce_button_identified = button;
    _debounce_timeout_start = millis();
    return NO_BUTTON;
  } else if (millis() < _debounce_timeout_start + BUTTON_DEBOUNCE_PERIOD) {
    // Same button as before, but timeout has not finished yet.
    return NO_BUTTON;
  }

  if (button != _last_button_pressed) {
    _record_button_press(button);
    return button;
  }

  // Check for holding down the plus or minus buttons
  if ( button == BUTTON_PLUS || button == BUTTON_MINUS ) {
    if ( millis() - BUTTON_PLUS_MINUS_REPEAT_DELAY > _time_button_pressed) {
      _record_button_press(button);
      return button;
    }
  }

  // Check for holding down the mode button
  if (
    button == BUTTON_MODE
    && millis() > BUTTON_MODE_HOLD_DOWN_DELAY + _time_button_pressed
  ) {
    return BUTTON_MODE_HELD_DOWN;
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
