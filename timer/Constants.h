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
#define PIN_DISPLAY_DIGIT_2  A3       // Display pin 2
#define PIN_DISPLAY_DIGIT_3  A4       // Display pin 6
#define PIN_DISPLAY_DIGIT_4  6        // Display pin 8

#define PIN_DISPLAY_SEGMENT_A A1      // Display pin 14
#define PIN_DISPLAY_SEGMENT_B A2      // Display pin 16
#define PIN_DISPLAY_SEGMENT_C 4       // Display pin 13
#define PIN_DISPLAY_SEGMENT_D 5       // Display pin 3
#define PIN_DISPLAY_SEGMENT_E A0      // Display pin 5
#define PIN_DISPLAY_SEGMENT_F 7       // Display pin 11
#define PIN_DISPLAY_SEGMENT_G 8       // Display pin 15
#define PIN_DISPLAY_SEGMENT_COLON 12  // Display pin 12

//Display brightness
#define DISPLAY_DIGIT_ON_TIME_MAX 200   // us
#define DISPLAY_DIGIT_ON_TIME_MIN 0   // us
#define DISPLAY_DIGIT_ON_TIME_CHANGE_INCREMENT 20 // us
#define DISPLAY_REDRAW_INTERVAL_MIN 1000  // us
#define DISPLAY_REDRAW_INTERVAL_MAX 15000  // us
#define DISPLAY_REDRAW_INTERVAL_CHANGE_INCREMENT 2000 // us


// Useful measures of time
#define ONE_MINUTE 60000
#define COUNTDOWN_SET_EXTRA_TIME 300 // ms
#define COUNTDOWN_DEFAULT_DURATION 900000 // 15 mins in ms
#define MAX_WAITING_IDLE 600000 // 10 mins in ms
#define POST_WAKEUP_BUTTON_IGNORE 500 // ms
#define STATE_MODE_TIMEOUT 5000 // 5 secs in ms


#endif
