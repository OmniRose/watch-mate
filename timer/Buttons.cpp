#include "Arduino.h"
#include "Buttons.h"


Buttons::Buttons() {
}

void Buttons::report() {
  int keyVal = analogRead(PIN_BUTTON_LADDER);

  // play the note corresponding to each value on A0
  if (keyVal >= 1020) {
    Serial.print("key 1: ");
    Serial.println(keyVal);
  }
  else if (keyVal >= 990 && keyVal <= 1010) {
    Serial.print("key 2: ");
    Serial.println(keyVal);
  }
  else if (keyVal >= 505 && keyVal <= 515) {
    Serial.print("key 3: ");
    Serial.println(keyVal);
  }
  else if (keyVal >= 5 && keyVal <= 10) {
    Serial.print("key 4: ");
    Serial.println(keyVal);
  }
  else {
    Serial.print("no key: ");
    Serial.println(keyVal);
  }
}
