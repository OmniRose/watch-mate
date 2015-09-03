
#include "Constants.h"
#include "Display.h"
#include "Buttons.h"

Display display;
Buttons buttons;

unsigned long countdown_ends;
unsigned long countdown_duration;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up!");

  buttons.setup();

  pinMode(13, OUTPUT);
  countdown_ends = 0;
  countdown_duration = 900000; // 15 mins in ms
  countdown_ends = millis() + countdown_duration;
}

void loop() {

  long time_remaining = countdown_ends - millis();

  display.displayTime( time_remaining / 1000 );

  int button = buttons.get_button_press();

  if ( button == BUTTON_MODE_HELD_DOWN ) {
    enter_shutdown_state();
    return;
  }

  if ( button == BUTTON_RESTART ) {
    // reset the start time
    countdown_ends = millis() + countdown_duration + 500;
  }

}

void enter_shutdown_state () {

  Serial.println("Starting shutdown...");
  long off_at = millis() + 3999;

  while ( buttons.get_button_press() == BUTTON_MODE_HELD_DOWN ) {
    long remaining = off_at - millis();
    if (remaining > 0) {
      display.displayTime( remaining / 1000 );

    } else {
      // enter infinite loop displaying 'off'. Power down will be handled by
      // external circuitry
      shutdown();
    }

  }

}

void shutdown () {
  Serial.println("OFF!");
  while (true) {
    delay(1000);
  }
}
