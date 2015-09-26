
// #include "toneAC.h"

#include "Constants.h"
#include "Display.h"
#include "Pulser.h"
#include "Speaker.h"
#include "Buttons.h"
#include "Countdown.h"
#include "Shutdown.h"

Display display;
Pulser  pulser;
Speaker speaker;
Buttons buttons;
Countdown countdown;
Shutdown shutdown;

#define STATE_WAITING  1
#define STATE_RUNNING  2
#define STATE_PULSING  3
#define STATE_BEEPING  4
#define STATE_ALARMING 5
#define STATE_MODE     6
#define STATE_DEBUG    7

// unsigned long countdown_ends;
// unsigned long countdown_duration;

int current_state = STATE_WAITING;
unsigned long current_state_last_changed;

bool should_sound_alarm = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up!");

  buttons.setup();

  // start in waiting state
  change_to_state(STATE_WAITING);

  // // set up for testing the transition to alarm state
  // change_to_state(STATE_RUNNING);
  // countdown.duration(10000); // 10 secs in ms
  // countdown.restart();
  // // should now cascade through states straight to alarm.
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

    case STATE_RUNNING:
      running_state_loop(button);
      break;

    case STATE_PULSING:
      pulsing_state_loop(button);
      break;

    case STATE_BEEPING:
      beeping_state_loop(button);
      break;

    case STATE_ALARMING:
      alarming_state_loop(button);
      break;

    case STATE_MODE:
      mode_state_loop(button);
      break;

    case STATE_DEBUG:
      debug_state_loop(button);
      break;

    default: // essentially state STATE_WAITING
      waiting_state_loop(button);
      break;

  }
}


void change_to_state(int new_state) {

  speaker.off();
  current_state_last_changed = millis();

  Serial.print("changing state from '");
  Serial.print(current_state);
  Serial.print("' to '");
  Serial.print(new_state);
  Serial.println("'.");

  if (new_state == STATE_WAITING) {
    current_state = STATE_WAITING;
  } else if (new_state == STATE_RUNNING) {
    current_state = STATE_RUNNING;
  } else if (new_state == STATE_PULSING) {
    current_state = STATE_PULSING;
  } else if (new_state == STATE_BEEPING) {
    current_state = STATE_BEEPING;
  } else if (new_state == STATE_ALARMING) {
    should_sound_alarm = true;
    current_state = STATE_ALARMING;
  } else if (new_state == STATE_MODE) {
    current_state = STATE_MODE;
  } else if (new_state == STATE_DEBUG) {
    Serial.println("ENTERING DEBUG MODE!");
    current_state = STATE_DEBUG;
  }
}

void waiting_state_loop (int button) {
  display.display_time( countdown.duration() / 1000 );

  if (millis() - current_state_last_changed > MAX_WAITING_IDLE) {
    // Timeout, shut down.
    shutdown.suspend();
    change_to_state(STATE_WAITING);
    return;
  }

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

  long time_overshot = - countdown.time_remaining();
  int alert_intensity = 1000; // max value

  if (time_overshot < BEEPING_MODE_EASE_IN_PERIOD) {
    // Serial.println(time_overshot);
    alert_intensity = time_overshot * 1000 / BEEPING_MODE_EASE_IN_PERIOD;
  }

  // sound_alert takes a value beteween 0 and 1000 that represents how hard to
  // try alerting. Lower is more gently, 1000 is full on.


  speaker.sound_alert(alert_intensity);
  pulser.flash();
  display.display_time( time_overshot / 1000 );

  // Special case the plus button.
  if ( button == BUTTON_PLUS ) {
    // Reset counter and add one minute
    countdown.change_end_time(ONE_MINUTE);
    change_to_state(STATE_RUNNING);
  } else {
    running_state_loop_buttons(button);
  }

  // After a certain period enter the alarming state
  if (time_overshot > BEEPING_MODE_DURATION) {
    return change_to_state(STATE_ALARMING);
  }

}

void alarming_state_loop (int button) {

  static bool first_time = true;
  if (first_time) Serial.println("in alarm state");
  first_time = false;

  pulser.flash();

  // When was a button last pressed - this is the last time we know that the
  // watchkeeper was on the boat.
  unsigned long time_since_last_seen = millis() - countdown.last_changed();
  display.display_time( time_since_last_seen / 1000 );

  // Only effect a button press can have is to silence the alarm. Exiting alarm
  // state is achieved by turning the device off by holding down the power/mode
  // button.
  if ( button != NO_BUTTON ) {
    should_sound_alarm = false;
  }

  // Make a noise if required.
  if (should_sound_alarm) {
    speaker.sound_alarm();
  } else {
    speaker.off();
  }

}

void running_state_loop_buttons (int button) {
  if ( button == BUTTON_RESTART ) {
    countdown.restart();
    change_to_state(STATE_RUNNING);
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

#define MODE_SUBSTATE_BRIGHTNESS 1
#define MODE_SUBSTATE_VOLUME     2


void mode_state_loop (int button) {

  static int substate = MODE_SUBSTATE_BRIGHTNESS;

  if (button == BUTTON_RESTART) {
    change_to_state(STATE_WAITING);
    return;
  } else if ( button == BUTTON_MODE ) {
    if (substate == MODE_SUBSTATE_BRIGHTNESS) {
      substate = MODE_SUBSTATE_VOLUME;
    } else if ( substate == MODE_SUBSTATE_VOLUME ) {
      substate = MODE_SUBSTATE_BRIGHTNESS;
    }
    return;
  }

  if (substate == MODE_SUBSTATE_BRIGHTNESS) {
    display.display_text( "bri" );

    if ( button == BUTTON_PLUS ) {
      display.brighter();
    } else if ( button == BUTTON_MINUS ) {
      display.dimmer();
    }

  } else if ( substate == MODE_SUBSTATE_VOLUME ) {
    display.display_text( "vol" );

    if ( button == BUTTON_PLUS ) {
      speaker.louder();
      speaker.beep();
    } else if ( button == BUTTON_MINUS ) {
      speaker.quieter();
      speaker.beep();
    }

  }


  // if we've been in mode state for a while not doing anything return to
  // waiting mode
  if (millis() - buttons.millis_last_button_pressed() > STATE_MODE_TIMEOUT) {
    change_to_state(STATE_WAITING);
    return;
  }
}


void enter_shutdown_state () {

  Serial.println("Starting shutdown...");
  long off_at = millis() + 2999;

  bool should_suspend = false;


  while ( buttons.get_button_press() == BUTTON_MODE_HELD_DOWN ) {
    long remaining = off_at - millis();
    char off[] = "OFF ";
    off[3] = int((remaining + 1000) / 1000) + 48; // to ascii code

    if (remaining > 0) {
      display.display_text( off );
    } else {
      should_suspend = true;
      display.display_text("    "); // blank the screen
    }
  }

  if (should_suspend) {

    shutdown.suspend();

    // On waking go back to waiting mode and return out of this loop
    buttons.reset();
    buttons.ignore_for(POST_WAKEUP_BUTTON_IGNORE);
    change_to_state(STATE_WAITING);
  }
}


void debug_state_loop(int button) {
  long now = millis();

  display.display_text("dbug");

  // // check that the buttons are working
  // int value = analogRead(PIN_BUTTON_LADDER);
  // while (millis() < now + 200 ) {
  //   // display value for 0.2 seconds
  //   display.display_number(value);
  // }

  // Sound the alarm until a button is pressed
  speaker.sound_alarm();
  if (buttons.get_button_press() != NO_BUTTON ) {
    change_to_state(STATE_WAITING);
  }

}

