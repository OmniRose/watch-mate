/*
  Constants.h - Constants for the timer project
*/
#ifndef Constants_h
#define Constants_h

#include "Arduino.h"


#define PIN_BUTTON_LADDER A5


#define PIN_DISPLAY_DIGIT_1  11       // Display pin 1
#define PIN_DISPLAY_DIGIT_2  10       // Display pin 2
#define PIN_DISPLAY_DIGIT_3  9        // Display pin 6
#define PIN_DISPLAY_DIGIT_4  6        // Display pin 8

#define PIN_DISPLAY_SEGMENT_A A1      //Display pin 14
#define PIN_DISPLAY_SEGMENT_B 3       //Display pin 16
#define PIN_DISPLAY_SEGMENT_C 4       //Display pin 13
#define PIN_DISPLAY_SEGMENT_D 5       //Display pin 3
#define PIN_DISPLAY_SEGMENT_E A0      //Display pin 5
#define PIN_DISPLAY_SEGMENT_F 7       //Display pin 11
#define PIN_DISPLAY_SEGMENT_G 8       //Display pin 15
#define PIN_DISPLAY_SEGMENT_COLON 12  // Display pin 12


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
