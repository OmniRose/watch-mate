
#include "Constants.h"
#include "Display.h"
#include "Buttons.h"

Display display;
Buttons buttons;

unsigned long countdown_ends;
unsigned long countdown_duration;

#define STATE_RUNNING 1

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

  // Get the button press here and pass it to the state loops later.
  int button = buttons.get_button_press();

  // Special case holding down the mode button as it has the same behaviour in
  // all the states.
  if ( button == BUTTON_MODE_HELD_DOWN ) {
    enter_shutdown_state();
    return;
  }

  int current_state = STATE_RUNNING;

  switch (current_state) {
    case STATE_RUNNING:
      long time_remaining = countdown_ends - millis();

      display.display_time( time_remaining / 1000 );


      if ( button == BUTTON_RESTART ) {
        // reset the start time
        countdown_ends = millis() + countdown_duration + 500;
      }
      break;
  }


}

void enter_shutdown_state () {

  Serial.println("Starting shutdown...");
  long off_at = millis() + 3999;

  while ( buttons.get_button_press() == BUTTON_MODE_HELD_DOWN ) {
    long remaining = off_at - millis();
    if (remaining > 0) {
      char off[] = "OFF ";
      off[3] = int(remaining / 1000) + 48; // to ascii code
      display.display_text( off );

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
    display.display_text("BYE");
  }
}
