
#include "Constants.h"
#include "Display.h"
#include "Buttons.h"

Display display;
Buttons buttons;

#define STATE_WAITING  1
#define STATE_RUNNING  2
#define STATE_PULSING  3
#define STATE_BEEPING  4
#define STATE_ALARMING 5
#define STATE_MODE     6

unsigned long countdown_ends;
unsigned long countdown_duration;

int current_state = STATE_WAITING;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up!");

  buttons.setup();

  pinMode(13, OUTPUT);
  countdown_ends = 0;
  countdown_duration = 900000; // 15 mins in ms

  // start in waiting state
  current_state = STATE_WAITING;
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

  switch (current_state) {

    case STATE_WAITING:
      waiting_state_loop(button);
      break;

    case STATE_RUNNING:
      running_state_loop(button);
      break;

  }


}


void change_to_waiting_state() {
  current_state = STATE_WAITING;
}

void change_to_mode_state() {
  Serial.println("FIXME - code up change_to_mode_state");
}

void waiting_state_loop (int button) {
  display.display_time( countdown_duration / 1000 );

  if (button == BUTTON_RESTART) {
    return start_countdown_timer();
  } else if ( button == BUTTON_MODE ) {
    return change_to_mode_state();
  } else if ( button == BUTTON_PLUS ) {
    countdown_duration += ONE_MINUTE;
  } else if ( button == BUTTON_MINUS && countdown_duration >= ONE_MINUTE ) {
    countdown_duration -= ONE_MINUTE;
  }
}

void start_countdown_timer () {
  countdown_ends = millis() + countdown_duration + 300;
  current_state = STATE_RUNNING;
}

void running_state_loop (int button) {
  long time_remaining = countdown_ends - millis();

  display.display_time( time_remaining / 1000 );
  running_state_loop_buttons(button);
}

void running_state_loop_buttons (int button) {
  if ( button == BUTTON_RESTART ) {
    start_countdown_timer();
  } else if ( button == BUTTON_MODE ) {
    change_to_waiting_state();
  } else if ( button == BUTTON_PLUS ) {
    countdown_ends += ONE_MINUTE;
    current_state = STATE_RUNNING;
  } else if ( button == BUTTON_MINUS ) {
    long time_remaining = countdown_ends - millis();
    if ( time_remaining > ONE_MINUTE ) {
      countdown_ends -= ONE_MINUTE;
      current_state = STATE_RUNNING;
    }
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
