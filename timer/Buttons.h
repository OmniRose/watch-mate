#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"
#include "Constants.h"

class Buttons
{
  public:
    Buttons();
    void report();
  private:
    int _get_current_button();
};

#endif