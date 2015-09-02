
#include "Constants.h"
#include "Display.h"
# include "Buttons.h"

Display display;
Buttons buttons;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(PIN_BUTTON_LADDER, INPUT);
}

void loop() {

  display.displayTime(millis()/1000);
  buttons.report();

}
