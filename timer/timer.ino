
#include "Constants.h"
#include "Display.h"
#include "Buttons.h"

Display display;
Buttons buttons;

unsigned long countdown_ends;
unsigned long countdown_duration;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  countdown_ends = 0;
  countdown_duration = 900000; // 15 mins in ms
  countdown_ends = millis() + countdown_duration;
}

void loop() {

  long time_remaining = countdown_ends - millis();

  display.displayTime( time_remaining / 1000 );

  int button = buttons.get_button_press();
  if ( button == BUTTON_RESTART ) {
    // reset the start time
    countdown_ends = millis() + countdown_duration + 500;
  }

}
