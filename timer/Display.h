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
    void brighter();
    void dimmer();
  private:
    void _display_digit(int, char);
    void _turn_segments_on(char);
    void _turn_all_segments_off();
    bool _is_pause_required();
    int _digit_on_time;
    int _redraw_interval;
    unsigned long _display_last_painted;
};

#endif