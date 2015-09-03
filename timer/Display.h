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
    void _turn_segments_on(int);
    void _turn_all_segments_off();
};

#endif