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
    void on();
    void off();
  private:
};

#endif
