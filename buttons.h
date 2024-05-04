#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

#define DURATION_SHORT_PRESS 800
#define DURATION_VERY_LONG_PRESS 2000




typedef void (*ButtonCallback)(void); 

class Button {
  int pin;
  bool has_been_pressed;
  unsigned long press_start;
  unsigned long release_start;
  ButtonCallback onPressFunction;
  ButtonCallback onHoldFunction;
  ButtonCallback onLongHoldFunction;
  ButtonCallback onVeryLongHoldFunction;
  ButtonCallback onLongPressFunction;
  ButtonCallback onVeryLongPressFunction;
  ButtonCallback onReleasedFunction;

  public:
    Button(int pin);
    void init();
    void read();
    unsigned long pressed_since();
    unsigned long released_since();

    void onPress(ButtonCallback f);
    void onHold(ButtonCallback f);
    void onLongHold(ButtonCallback f);
    void onVeryLongHold(ButtonCallback f);
    void onLongPress(ButtonCallback f);
    void onVeryLongPress(ButtonCallback f);
    void onReleased(ButtonCallback f);

    void reset();
};

Button::Button(int pin) {
  this->pin = pin;
}

void Button::init() {
  pinMode(this->pin, INPUT_PULLUP);
  this->has_been_pressed = false;
  this->press_start = 0;
  this->release_start = 0;
}

void Button::read() {
  int is_pressed = !digitalRead(this->pin);
  
  if (is_pressed && this->press_start == 0) {
    this->press_start = millis();
  }
  if (!is_pressed && this->has_been_pressed && this->release_start == 0) {
    this->release_start = millis();
  }

  unsigned long pressed_since = this->pressed_since();
  unsigned long released_since = this->released_since();
  
  if (is_pressed) {
    // Fire the callback function all the time while this is being pressed
    if (this->onHoldFunction) { this->onHoldFunction(); }

    if (this->pressed_since() > 1000 && this->pressed_since() <= 5000) {
      if (this->onLongHoldFunction) { this->onLongHoldFunction(); }
    }
    if (this->pressed_since() > 5000) {
      if (this->onVeryLongHoldFunction) { this->onVeryLongHoldFunction(); }
    }
    // Serial.print("Pressed since ");
    // Serial.println(pressed_since);
    if ( released_since > 100) {
      this->has_been_pressed = false;
    }
  } else {
    // Not pressed.
    if (!this->has_been_pressed) {
      if (pressed_since > 0 && pressed_since < DURATION_SHORT_PRESS) {
        if (this->onPressFunction) { this->onPressFunction(); }
        // Serial.print("Short Press (released after ");
        // Serial.print(pressed_since);
        // Serial.print(", released since ");
        // Serial.print(released_since);
      } else if (pressed_since > 0 &&  pressed_since < DURATION_VERY_LONG_PRESS) {
        if (this->onLongPressFunction) { this->onLongPressFunction(); }
        // Serial.print("Long Press (released after ");
        // Serial.print(pressed_since);
        // Serial.println(")");
      } else if (pressed_since > 0 && pressed_since >= DURATION_VERY_LONG_PRESS) {
        if (this->onVeryLongPressFunction) { this->onVeryLongPressFunction(); }
        // Serial.print("Very Long Press (released after ");
        // Serial.print(pressed_since);
        // Serial.println(")");
      }
      this->press_start = 0;
      this->has_been_pressed = true;
      this->release_start = millis();
      if (this->onReleasedFunction) { this->onReleasedFunction(); }
    }
  }
}

unsigned long Button::pressed_since() {
  if ( this->press_start == 0) {
    return 0;
  }
  return millis() - this->press_start;
}

unsigned long Button::released_since() {
  if ( this->release_start == 0) {
    return 0;
  }
  return millis() - this->release_start;
}

void Button::onPress(ButtonCallback f) {
  this->onPressFunction = f;
}

void Button::onHold(ButtonCallback f) {
  this->onHoldFunction = f;
}

void Button::onLongHold(ButtonCallback f) {
  this->onLongHoldFunction = f;
}

void Button::onVeryLongHold(ButtonCallback f) {
  this->onVeryLongHoldFunction = f;
}

void Button::onLongPress(ButtonCallback f) {
  this->onLongPressFunction = f;
}

void Button::onVeryLongPress(ButtonCallback f) {
  this->onVeryLongPressFunction = f;
}

void Button::onReleased(ButtonCallback f) {
  this->onReleasedFunction = f;
}

void Button::reset() {
  this->onPressFunction = NULL;
  this->onHoldFunction = NULL;
  this->onLongPressFunction = NULL;
  this->onVeryLongPressFunction = NULL;
}


#endif
