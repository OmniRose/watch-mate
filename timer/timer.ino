
#include "Constants.h"
#include "Display.h"
#include "Buttons.h"

Display display;
Buttons buttons;

unsigned long start_time = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  start_time = millis();
}

void loop() {

  unsigned long current_time = millis() - start_time;
  display.displayTime( current_time / 1000 );

  int button = buttons.get_button_press();
  if ( button == BUTTON_RESTART ) {
    // reset the start time
    start_time = millis();
  }

}
