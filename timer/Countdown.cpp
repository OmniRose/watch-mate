#include "Arduino.h"
#include "Countdown.h"

Countdown::Countdown() {
  _duration = COUNTDOWN_DEFAULT_DURATION;
}

long Countdown::duration() {
  return _duration;
}

void Countdown::duration(long duration) {
  _duration = duration;
}

void Countdown::change_duration(long delta) {

  long new_duration = _duration + delta;

  if (new_duration > 0 ) {
    _duration = new_duration;
  }

  _countdown_last_changed = millis();
}

void Countdown::restart() {
  _countdown_ends = millis() + _duration + COUNTDOWN_SET_EXTRA_TIME;

  _countdown_last_changed = millis();
}

void Countdown::change_end_time(long delta) {

  long new_time_remaining = time_remaining() + delta;

  if (new_time_remaining > 0) {
    _countdown_ends = millis() + new_time_remaining;
  }

  _countdown_last_changed = millis();
}

unsigned long Countdown::last_changed() {
  return _countdown_last_changed;
}


long Countdown::time_remaining() {
  return _countdown_ends - millis();
}

long Countdown::time_remaining_seconds() {
  return time_remaining() / 1000;
}
