#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"
#include "Constants.h"

// use these to identify the button pressed in the code
#define NO_BUTTON       0
#define BUTTON_MODE     1
#define BUTTON_PLUS     2
#define BUTTON_MINUS    3
#define BUTTON_RESTART  4

// Time in milliseconds after which holding donw the plus or minus button
// results in a new press being registered.
#define BUTTON_PLUS_MINUS_REPEAT_DELAY 300

// min and max values reod from the analogue input that match up to the button
// being pressed.
#define BUTTON_MODE_MAX_VALUE     1023
#define BUTTON_MODE_MIN_VALUE     1020
#define BUTTON_PLUS_MAX_VALUE     1010
#define BUTTON_PLUS_MIN_VALUE      990
#define BUTTON_MINUS_MAX_VALUE     515
#define BUTTON_MINUS_MIN_VALUE     505
#define BUTTON_RESTART_MAX_VALUE    10
#define BUTTON_RESTART_MIN_VALUE     5

class Buttons
{
  public:
    Buttons();
    int get_button_press();
  private:
    void _record_button_press(int);
    int _get_current_button();
    int _last_button_pressed;
    unsigned long _time_button_pressed;
};

#endif