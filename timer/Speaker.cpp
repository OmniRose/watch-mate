#include "Arduino.h"
#include "Speaker.h"

Speaker::Speaker() {
  pinMode(PIN_SPEAKER, OUTPUT);
}

void Speaker::beep() {
  tone(PIN_SPEAKER, 1046, 200);
}

void Speaker::on() {

  int point_in_period = millis() % PULSER_FLASH_PERIOD;
  int cutoff = PULSER_FLASH_PERIOD * 0.5;

  if ( point_in_period > cutoff ) {
    tone(PIN_SPEAKER, 1046);
  } else {
    noTone(PIN_SPEAKER);
  }

}


void Speaker::off() {
  noTone(PIN_SPEAKER);
}
