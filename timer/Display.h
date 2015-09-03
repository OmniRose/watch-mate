#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "Constants.h"

class Display
{
  public:
    Display();
    void display_time(int);
    void display_text(char*);
  private:
    void _display_digit(int, char);
    void _turn_segments_on(char);
    void _turn_all_segments_off();
    void _pause_if_required();
    unsigned long _display_last_painted;
};

#endif