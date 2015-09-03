# States

The watch timer is essentially a state machine. This document is for hashing
out what those states are before committing them to code.

After startup the timer switches to the *Waiting* state.

## All states

Some button presses have an action in all states. They are:

Button           | Effect
---------------- | ---
mode (held down) | Switches to `shutting down` state.

## Waiting

Timer is not running. Display is the countdown period. After `MAX_WAITING_IDLE` minutes in waiting mode timer will switch to *off* state.

Button  | Effect
------- | ---
mode    | Switches to *mode* state
plus    | Increments the countdown duration minutes
minus   | Decrements the countdown duration minutes
restart | Starts the countdown, switches to *running* mode

## Running

Timer is running so values are counting down. Will switch to *pulsing* mode if countdown remaining falls below `PULSING_START_TIME`.

Button  | Effect
------- | ---
mode    | Switches to *waiting* state
plus    | Adds a minute to the current countdown, switches to *running* state
minus   | Subtracts a minute to the current countdown, switches to *running* state
restart | Restarts the countdown

## Pulsing

Timer is running so values are counting down. Timer display is also pulsing. Switches to *beeping* if countdown below zero.

Button  | Effect
------- | ---
mode    | As *running*
plus    | As *running*
minus   | As *running*
restart | As *running*

## Beeping

Timer flashes zeros. Beeper makes a noise. Will switch to *alarming* state if countdown falls below `ALARMING_START_TIME`.

Button  | Effect
------- | ---
mode    | As *running*
plus    | Sets countdown to one minute, switches to *running* state
minus   | No effect
restart | As *running*

## Alarming

Timer counts up from the last time any button was pressed before alarming state was entered. Display flashes. Siren is activated. Only way to exit *alarming* state is to turn the timer off and on again.

Button  | Effect
------- | ---
mode    | Silences siren
plus    | Silences siren
minus   | Silences siren
restart | Silences siren

## Mode

Lets user change some values such as volume of beeper, brightness. Value is saved when it is changed.

Button  | Effect
------- | ---
mode    | Switches between the various mode options (volume, brightness)
plus    | Increase the selected value
minus   | Decrease the selected value
restart | Switch to *waiting* state

## Shutting down

State before unit switches itself off. As long as user is holding down the mode button this state is maintained. Initially it displays "OFF" and then does a countdown. If the countdown reaches 0 then enters *off* state.

If user releases mode button then returns to either *waiting* or *alarming* states.

## Off

Unit is turning itself off. Should display "BYE" on screen, save any settings to EEPROM and then power itself down after a second or so. Button presses have no effect.