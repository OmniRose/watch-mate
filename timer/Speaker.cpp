#include "Arduino.h"
#include "Speaker.h"
#include "toneAC.h"

Speaker::Speaker() {
  _volume = SPEAKER_VOLUME_MAX;
  _frequency = SPEAKER_BEEP_FREQUENCY_DEFAULT;
}


void Speaker::higher_pitch() {
  _frequency = min(_frequency + SPEAKER_BEEP_FREQUENCY_CHANGE_INCREMENT, SPEAKER_BEEP_FREQUENCY_MAX);
}

void Speaker::lower_pitch() {
  _frequency = max(_frequency - SPEAKER_BEEP_FREQUENCY_CHANGE_INCREMENT, SPEAKER_BEEP_FREQUENCY_MIN);
}


void Speaker::louder() {
  _volume = min(_volume + SPEAKER_VOLUME_CHANGE_INCREMENT, SPEAKER_VOLUME_MAX);
}

void Speaker::quieter() {
  _volume = max(_volume - SPEAKER_VOLUME_CHANGE_INCREMENT, SPEAKER_VOLUME_MIN);
}


void Speaker::beep() {
  toneAC(_frequency, _volume, SPEAKER_DEMO_BEEP_DURATION, true);
}

void Speaker::sound_alert(int intensity) {

  // From the intensity work out how loud to be. The "+1" at the end is so that
  // the values reach their full value at the end. Especially important for the
  // volume.
  int alert_volume = map(intensity, 0, 1000, 1, _volume + 1);
  int alert_period = map(intensity, 0, 1000, SPEAKER_ALERT_PERIOD_INITIAL, SPEAKER_ALERT_PERIOD_FINAL + 1);
  int alert_length = map(intensity, 0, 1000, SPEAKER_ALERT_ON_INITIAL, SPEAKER_ALERT_ON_FINAL + 1);

  int point_in_period = millis() % alert_period;

  if ( point_in_period < alert_length ) {
    toneAC(_frequency, alert_volume, 0, true);
  } else {
    noToneAC();
  }

}

void Speaker::sound_alarm() {

  int point_in_cycle = millis() % (SPEAKER_ALARM_BEEPING_DURATION + SPEAKER_ALARM_WHITE_NOISE_DURATION);
  bool beeping_on = point_in_cycle <= SPEAKER_ALARM_BEEPING_DURATION;

  if ( beeping_on) {

    bool rapid_pulse_on = point_in_cycle % (SPEAKER_ALARM_PULSE_DURATION * 2) > SPEAKER_ALARM_PULSE_DURATION;

    if (rapid_pulse_on) {
      toneAC(SPEAKER_ALARM_BEEP_FREQUENCY, SPEAKER_ALARM_VOLUME, 0, true);
    } else {
      noToneAC();
    }
  } else {

    // generate some white noise
    int white_noise_frequency = random(
      SPEAKER_ALARM_WHITE_NOISE_FREQUENCY_LOW,
      SPEAKER_ALARM_WHITE_NOISE_FREQUENCY_HIGH
    );
    toneAC(white_noise_frequency, SPEAKER_ALARM_VOLUME, 0, true);
  }

}


void Speaker::off() {
  noToneAC();
}
