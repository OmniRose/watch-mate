#include "Arduino.h"
#include "Speaker.h"
#include "toneAC.h"

Speaker::Speaker() {
  _volume = SPEAKER_VOLUME_MAX;
}

void Speaker::louder() {
  _volume = min(_volume + SPEAKER_VOLUME_CHANGE_INCREMENT, SPEAKER_VOLUME_MAX);
}

void Speaker::quieter() {
  _volume = max(_volume - SPEAKER_VOLUME_CHANGE_INCREMENT, SPEAKER_VOLUME_MIN);
}


void Speaker::beep() {
  toneAC(SPEAKER_BEEP_FREQUENCY, _volume, 200, true);
}

void Speaker::on() {

  int point_in_period = millis() % PULSER_FLASH_PERIOD;
  int cutoff = PULSER_FLASH_PERIOD * 0.5;

  if ( point_in_period > cutoff ) {
    toneAC(SPEAKER_BEEP_FREQUENCY, _volume, 0, true);
  } else {
    noToneAC();
  }

}


void Speaker::off() {
  noToneAC();
}
