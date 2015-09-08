#include "Arduino.h"
#include "Pulser.h"
#include "fscale.h"

Pulser::Pulser() {
  pinMode(PIN_PULSE_LED, OUTPUT);
  _pulse_last_painted = 0;
}

void Pulser::pulse() {

  // Don't pulse again if it is too soon.

  if ( micros() - _pulse_last_painted < PULSER_OFF_INTERVAL ) {
    return;
  }

  int max_on = _get_max_on_time();

  // keep this code as fast as possible - calculate max_on above.
  digitalWrite(PIN_PULSE_LED, HIGH);
  delayMicroseconds(max_on);
  digitalWrite(PIN_PULSE_LED, LOW);

  _pulse_last_painted = micros();
}


int Pulser::_get_max_on_time () {

  float pi = 3.14159;
  int point_in_loop_millis = millis() % PULSE_DURATION;
  float point_in_loop_fraction = point_in_loop_millis / float(PULSE_DURATION);
  float point_in_loop_radians = 2 * pi * point_in_loop_fraction;

  float amount_on = (cos(point_in_loop_radians) + 1) / 2;
  int max_on = PULSER_MAX_ON_TIME * amount_on;

  return max_on;
}
