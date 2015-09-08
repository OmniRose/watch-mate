#include "Arduino.h"
#include "Pulser.h"

Pulser::Pulser() {
  pinMode(PIN_PULSE_LED, OUTPUT);
  _pulse_last_painted = 0;
}

void Pulser::pulse() {

  // Don't pulse again if it is too soon.

  if ( micros() - _pulse_last_painted < PULSER_OFF_INTERVAL ) {
    return;
  }

  digitalWrite(PIN_PULSE_LED, HIGH);
  delayMicroseconds(PULSER_MAX_ON_TIME);
  digitalWrite(PIN_PULSE_LED, LOW);

  _pulse_last_painted = micros();
}


