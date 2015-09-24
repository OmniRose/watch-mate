#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"
#include "Constants.h"

// use these to identify the button pressed in the code
#define NO_BUTTON             0
#define BUTTON_MODE           1
#define BUTTON_PLUS           2
#define BUTTON_MINUS          3
#define BUTTON_RESTART        4
#define BUTTON_MODE_HELD_DOWN 5

// Time in milliseconds that a button needs to be held down for to count as an
// actualy button press.
#define BUTTON_DEBOUNCE_PERIOD 50

// Time in milliseconds after which holding donw the plus or minus button
// results in a new press being registered.
#define BUTTON_PLUS_MINUS_REPEAT_DELAY 300

// Time in ms after which holding down the mode button results in the
// BUTTON_MODE_HELD_DOWN value being returned.
#define BUTTON_MODE_HOLD_DOWN_DELAY 2000

// min and max values reod from the analogue input that match up to the button
// being pressed.
#define BUTTON_PLUS_MAX_VALUE     1023
#define BUTTON_PLUS_MIN_VALUE     1020
#define BUTTON_MINUS_MAX_VALUE    1010
#define BUTTON_MINUS_MIN_VALUE     990
#define BUTTON_RESTART_MAX_VALUE   515
#define BUTTON_RESTART_MIN_VALUE   505

class Buttons
{
  public:
    Buttons();
    void setup();
    void reset();
    int get_button_press();
    unsigned long millis_last_button_pressed();
    void ignore_for(long);
  private:
    void _record_button_press(int);
    int _get_current_button();
    int _last_button_pressed;
    unsigned long _debounce_button_identified;
    unsigned long _debounce_timeout_start;
    unsigned long _time_button_pressed;
    unsigned long _ignore_buttons_until;
};

#endif