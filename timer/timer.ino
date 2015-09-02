
#include "Constants.h"
#include "Display.h"

Display display;

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  display.displayTime(millis()/1000);
}


