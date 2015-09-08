#include "Arduino.h"
#include "Display.h"

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

Display::Display() {
  pinMode(PIN_DISPLAY_SEGMENT_A, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_B, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_C, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_D, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_E, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_F, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_G, OUTPUT);
  pinMode(PIN_DISPLAY_SEGMENT_COLON, OUTPUT);

  pinMode(PIN_DISPLAY_DIGIT_1, OUTPUT);
  pinMode(PIN_DISPLAY_DIGIT_2, OUTPUT);
  pinMode(PIN_DISPLAY_DIGIT_3, OUTPUT);
  pinMode(PIN_DISPLAY_DIGIT_4, OUTPUT);

  digitalWrite(PIN_DISPLAY_SEGMENT_COLON, SEGMENT_OFF);
}

void Display::display_text(char* text) {
  // Serial.println(text);

  if (_is_pause_required()) return;

  _display_digit(PIN_DISPLAY_DIGIT_1, text[0]);
  _display_digit(PIN_DISPLAY_DIGIT_2, text[1]);
  _display_digit(PIN_DISPLAY_DIGIT_3, text[2]);
  _display_digit(PIN_DISPLAY_DIGIT_4, text[3]);

  _display_last_painted = micros();
}

void Display::display_time(int toDisplay) {


  int minutes = toDisplay / 60;
  int seconds = toDisplay % 60;
  char numbers_as_letters[] = "0123456789";

  if (_is_pause_required()) return;

  _display_digit(PIN_DISPLAY_DIGIT_1, ':');
  _display_digit(PIN_DISPLAY_DIGIT_1, numbers_as_letters[minutes / 10 % 10]);
  _display_digit(PIN_DISPLAY_DIGIT_2, numbers_as_letters[minutes % 10     ]);
  _display_digit(PIN_DISPLAY_DIGIT_3, numbers_as_letters[seconds / 10     ]);
  _display_digit(PIN_DISPLAY_DIGIT_4, numbers_as_letters[seconds % 10     ]);

  _display_last_painted = micros();
}

bool Display::_is_pause_required() {
  return micros() - _display_last_painted < DISPLAY_OFF_INTERVAL;
}

void Display::_display_digit(int digit, char toDisplay) {
  _turn_segments_on(toDisplay);
  digitalWrite(digit, DIGIT_ON);
  delayMicroseconds(DISPLAY_MAX_ON_TIME);
  digitalWrite(digit, DIGIT_OFF);
  _turn_all_segments_off();
}

void Display::_turn_all_segments_off () {
  digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_OFF);
  digitalWrite(PIN_DISPLAY_SEGMENT_COLON, SEGMENT_OFF);
}

// Given a number, turns on those segments
void Display::_turn_segments_on(char charToDisplay) {

  // TODO - change all these to use a byte per char and the bits in the byte to
  // represent the segments in the LED display.

  switch (charToDisplay) {

  case ' ':
  case 0: // nul
    _turn_all_segments_off();
    break;

  case '0':
  case 'O':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    break;

  case '1':
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    break;

  case '2':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case '3':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case '4':
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case '5':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case '6':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case '7':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    break;

  case '8':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case '9':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'B':
  case 'b':
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'i':
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    break;

  case 'E':
  case 'e':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'F':
    digitalWrite(PIN_DISPLAY_SEGMENT_A, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'l':
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    break;

  case 'o':
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'R':
  case 'r':
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'Y':
    digitalWrite(PIN_DISPLAY_SEGMENT_B, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_F, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_G, SEGMENT_ON);
    break;

  case 'v':
    digitalWrite(PIN_DISPLAY_SEGMENT_C, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_D, SEGMENT_ON);
    digitalWrite(PIN_DISPLAY_SEGMENT_E, SEGMENT_ON);
    break;

  case ':': // Only works when PIN_DISPLAY_DIGIT_1 in active...
    digitalWrite(PIN_DISPLAY_SEGMENT_COLON, SEGMENT_ON);
    break;

  default:
    Serial.print("ERROR - can't light up segment for ascii decimal '");
    Serial.print((int)charToDisplay);
    Serial.println("'");
    break;

  }
}
