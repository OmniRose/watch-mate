/*
  Constants.h - Constants for the timer project
*/
#ifndef Constants_h
#define Constants_h

#include "Arduino.h"

//Display brightness
//
//Each digit is on for a certain amount of microseconds Then it is off until we
//have reached a total of DISPLAY_LOOP_TIME for the function call Let's assume
//each digit is on for 1000us
//
//Each digit is on for 1ms, there are 4 digits, so the display is off for 16ms.
//That's a ratio of 1ms to 16ms or 6.25% on time (PWM). Let's define a variable
//called brightness that varies from:
//
//5000 blindingly bright (15.7mA current draw per digit)
//2000 shockingly bright (11.4mA current draw per digit)
//1000 pretty bright (5.9mA)
//500 normal (3mA)
//200 dim but readable (1.4mA)
//50 dim but readable (0.56mA)
//5 dim but readable (0.31mA)
//1 dim but readable in dark (0.28mA)
#define DISPLAY_BRIGHTNESS  500
#define DISPLAY_LOOP_TIME 10

#endif
