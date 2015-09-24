/*
  Constants.h - Constants for the timer project
*/
#ifndef Constants_h
#define Constants_h

#include "Arduino.h"


#define PIN_MODE_BUTTON 2
#define PIN_BUTTON_LADDER A5

#define WAKE_FROM_SLEEP_INTERRUPT 0 // hardcoded to pin 2


#define PIN_PULSE_LED 13
#define PULSER_MAX_ON_TIME  200   // us
#define PULSER_OFF_INTERVAL 500  // us
#define PULSE_DURATION 2000 // ms
#define PULSER_FLASH_PERIOD 800 // ms
#define PULSE_STARTS_AT 120000 // 2 mins in ms


#define PIN_SPEAKER 3


#define PIN_DISPLAY_DIGIT_1  11       // Display pin 1
#define PIN_DISPLAY_DIGIT_2  10       // Display pin 2
#define PIN_DISPLAY_DIGIT_3  9        // Display pin 6
#define PIN_DISPLAY_DIGIT_4  6        // Display pin 8

#define PIN_DISPLAY_SEGMENT_A A1      //Display pin 14
#define PIN_DISPLAY_SEGMENT_B A2      //Display pin 16
#define PIN_DISPLAY_SEGMENT_C 4       //Display pin 13
#define PIN_DISPLAY_SEGMENT_D 5       //Display pin 3
#define PIN_DISPLAY_SEGMENT_E A0      //Display pin 5
#define PIN_DISPLAY_SEGMENT_F 7       //Display pin 11
#define PIN_DISPLAY_SEGMENT_G 8       //Display pin 15
#define PIN_DISPLAY_SEGMENT_COLON 12  // Display pin 12

//Display brightness
//
//Each digit is on for a certain amount of microseconds Then it is off until we
//have reached a total of DISPLAY_OFF_INTERVAL for the function call Let's assume
//each digit is on for 1000us
//
//Each digit is on for 1ms, there are 4 digits, so the display is off for 16ms.
//That's a ratio of 1ms to 16ms or 6.25% on time (PWM). Let's define a variable
//called brightness that varies from:
//
// WITH DISPLAY_OFF_INTERVAL of 1000 us
//   500 blindingly bright (15.7mA current draw per digit)
//   200 shockingly bright (11.4mA current draw per digit)
//   100 pretty bright (5.9mA)
//   50 normal (3mA)
//   20 dim but readable (1.4mA)
//   5 dim but readable (0.56mA)
//
// WITH DISPLAY_OFF_INTERVAL of 10000 us
//   5 dim but readable (0.31mA)
//   1 dim but readable in dark (0.28mA)
#define DISPLAY_MAX_ON_TIME  50   // us
#define DISPLAY_OFF_INTERVAL 1000 // us


// Useful measures of time
#define ONE_MINUTE 60000
#define COUNTDOWN_SET_EXTRA_TIME 300 // ms
#define COUNTDOWN_DEFAULT_DURATION 900000 // 15 mins in ms
#define MAX_WAITING_IDLE 600000 // 10 mins in ms
#define POST_WAKEUP_BUTTON_IGNORE 500 // ms
#define STATE_MODE_TIMEOUT 5000 // 5 secs in ms


#endif
