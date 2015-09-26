#ifndef Countdown_h
#define Countdown_h

#include "Arduino.h"
#include "Constants.h"

class Countdown
{
  public:
    Countdown();
    void duration(long);
    void change_duration(long);
    long duration();
    void restart();
    void change_end_time(long);
    unsigned long last_changed();
    long time_remaining();
    long time_remaining_seconds();
  private:
    unsigned long _countdown_ends;
    unsigned long _countdown_last_changed;
    unsigned long _duration;
};

#endif
