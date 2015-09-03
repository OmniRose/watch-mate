#include "Arduino.h"
#include "Buttons.h"


// use these to identify the button pressed in the code
#define NO_BUTTON 0
#define BUTTON_1  1
#define BUTTON_2  2
#define BUTTON_3  3
#define BUTTON_4  4

// min and max values reod from the analogue input that match up to the button
// being pressed.
#define BUTTON_1_MAX_VALUE 1023
#define BUTTON_1_MIN_VALUE 1020
#define BUTTON_2_MAX_VALUE 1010
#define BUTTON_2_MIN_VALUE 990
#define BUTTON_3_MAX_VALUE 515
#define BUTTON_3_MIN_VALUE 505
#define BUTTON_4_MAX_VALUE 10
#define BUTTON_4_MIN_VALUE 5





Buttons::Buttons() {
}

void Buttons::report() {
  int key = _get_current_button();
  Serial.print("current key: ");
  Serial.println(key);
}

int Buttons::_get_current_button() {
  int button_pin_value = analogRead(PIN_BUTTON_LADDER);

  // Serial.print("key value: ");
  // Serial.println(button_pin_value);

  if (button_pin_value >= BUTTON_1_MIN_VALUE && button_pin_value <= BUTTON_1_MAX_VALUE) {
    return BUTTON_1;
  }
  else if (button_pin_value >= BUTTON_2_MIN_VALUE && button_pin_value <= BUTTON_2_MAX_VALUE) {
    return BUTTON_2;
  }
  else if (button_pin_value >= BUTTON_3_MIN_VALUE && button_pin_value <= BUTTON_3_MAX_VALUE) {
    return BUTTON_3;
  }
  else if (button_pin_value >= BUTTON_4_MIN_VALUE && button_pin_value <= BUTTON_4_MAX_VALUE) {
    return BUTTON_4;
  }
  else {
    return NO_BUTTON;
  }
}
