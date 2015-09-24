#include "Arduino.h"
#include "Speaker.h"
#include "toneAC.h"

Speaker::Speaker() {
  // pinMode(PIN_SPEAKER, OUTPUT);
}

void Speaker::beep() {
  toneAC(2000, 5, 200, true);
}

void Speaker::on() {

  int point_in_period = millis() % PULSER_FLASH_PERIOD;
  int cutoff = PULSER_FLASH_PERIOD * 0.5;

  if ( point_in_period > cutoff ) {
    toneAC(1046, 5, 0, true);
  } else {
    noToneAC();
  }

}


void Speaker::off() {
  noToneAC();
}
