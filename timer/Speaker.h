#ifndef Speaker_h
#define Speaker_h

#include "Arduino.h"
#include "Constants.h"
#include "toneAC.h"

class Speaker
{
  public:
    Speaker();
    void beep();
    void louder();
    void quieter();
    void higher_pitch();
    void lower_pitch();
    void sound_alert(int);
    void sound_alarm();
    void off();
  private:
    int _frequency;
    int _volume;
};

#endif
