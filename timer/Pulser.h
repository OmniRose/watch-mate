#ifndef Pulser_h
#define Pulser_h

#include "Arduino.h"
#include "Constants.h"

class Pulser
{
  public:
    Pulser();
    void pulse();
  private:
    unsigned long _pulse_last_painted;
    int _get_max_on_time();
};

#endif