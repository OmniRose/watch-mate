#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "Constants.h"

class Display
{
  public:
    Display();
    void displayTime(int);
  private:
    void _lightNumber(int);
};

#endif