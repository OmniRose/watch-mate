
#include "Constants.h"
#include "Display.h"
#include "Pulser.h"
#include "Speaker.h"
#include "Buttons.h"
#include "Countdown.h"

Display display;
Pulser  pulser;
Speaker speaker;
Buttons buttons;
Countdown countdown;

#define STATE_WAITING  1
#define STATE_RUNNING  2
#define STATE_PULSING  3
#define STATE_BEEPING  4
#define STATE_ALARMING 5
#define STATE_MODE     6

// unsigned long countdown_ends;
// unsigned long countdown_duration;

int current_state = STATE_WAITING;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up!");

  buttons.setup();

  countdown.duration(90000); // 15 mins in ms
  // countdown_ends = 0;
  // countdown_duration = 900000; // 15 mins in ms

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

    case STATE_PULSING:
      pulsing_state_loop(button);
      break;

    case STATE_BEEPING:
      beeping_state_loop(button);
      break;

  }


}


void change_to_state(int new_state) {

  speaker.off();

  if (new_state == STATE_WAITING) {
    current_state = STATE_WAITING;
  } else if (new_state == STATE_RUNNING) {
    current_state = STATE_RUNNING;
  } else if (new_state == STATE_PULSING) {
    current_state = STATE_PULSING;
  } else if (new_state == STATE_BEEPING) {
    current_state = STATE_BEEPING;
  } else if (new_state == STATE_MODE) {
    Serial.println("FIXME - code up change_to_state(STATE_MODE)");
    change_to_state(STATE_WAITING);
  }
}

void waiting_state_loop (int button) {
  display.display_time( countdown.duration() / 1000 );

  if (button == BUTTON_RESTART) {
    countdown.restart();
    change_to_state(STATE_RUNNING);
  } else if ( button == BUTTON_MODE ) {
    change_to_state(STATE_MODE);
  } else if ( button == BUTTON_PLUS ) {
    countdown.change_duration(ONE_MINUTE);
  } else if ( button == BUTTON_MINUS ) {
    countdown.change_duration(-ONE_MINUTE);
  }
}

void running_state_loop (int button) {
  if (countdown.time_remaining() < PULSE_STARTS_AT) {
    return change_to_state(STATE_PULSING);
  }

  display.display_time( countdown.time_remaining_seconds() );

  running_state_loop_buttons(button);
}

void pulsing_state_loop (int button) {
  long time_remaining = countdown.time_remaining();

  if (time_remaining <= 0) {
    return change_to_state(STATE_BEEPING);
  }

  if (time_remaining > PULSE_STARTS_AT / 2) {
    pulser.pulse();
  } else {
    pulser.flash();
  }

  display.display_time( time_remaining / 1000 );

  running_state_loop_buttons(button);
}

void beeping_state_loop (int button) {

  speaker.on();
  pulser.flash();
  display.display_time( 0 );

  // Special case the plus button.
  if ( button == BUTTON_PLUS ) {
    // Reset counter and add one minute
    countdown.change_end_time(ONE_MINUTE);
    change_to_state(STATE_RUNNING);
  } else {
    running_state_loop_buttons(button);
  }

}

void running_state_loop_buttons (int button) {
  if ( button == BUTTON_RESTART ) {
    countdown.restart();
  } else if ( button == BUTTON_MODE ) {
    change_to_state(STATE_WAITING);
  } else if ( button == BUTTON_PLUS ) {
    countdown.change_end_time(ONE_MINUTE);
    change_to_state(STATE_RUNNING);
  } else if ( button == BUTTON_MINUS ) {
    countdown.change_end_time(-ONE_MINUTE);
    change_to_state(STATE_RUNNING);
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
