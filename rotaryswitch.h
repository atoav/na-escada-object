#ifndef RotarySwitch_h
#define RotarySwitch_h

#include "Arduino.h"

#define DURATION_SHORT_PRESS 800
#define DURATION_VERY_LONG_PRESS 2000




typedef void (*RotarySwitchCallback)(void); 

class RotarySwitch {
  int pins[8];
  bool has_been_pressed;
  unsigned long press_start;
  unsigned long release_start;
  RotarySwitchCallback onChangeFunction;
  RotarySwitchCallback onMode1Function;
  RotarySwitchCallback onMode2Function;
  RotarySwitchCallback onMode3Function;
  RotarySwitchCallback onMode4Function;
  RotarySwitchCallback onMode5Function;
  RotarySwitchCallback onMode6Function;
  RotarySwitchCallback onMode7Function;
  RotarySwitchCallback onMode8Function;


  public:
    RotarySwitch(int pins[8]);
    void init();
    void read();
    int last_mode;

    void onChange(RotarySwitchCallback f);
    void onMode1(RotarySwitchCallback f);
    void onMode2(RotarySwitchCallback f);
    void onMode3(RotarySwitchCallback f);
    void onMode4(RotarySwitchCallback f);
    void onMode5(RotarySwitchCallback f);
    void onMode6(RotarySwitchCallback f);
    void onMode7(RotarySwitchCallback f);
    void onMode8(RotarySwitchCallback f);

    void reset();
};

RotarySwitch::RotarySwitch(int pins[8]) {
  for (int n=0; n<8; n++) {
    this->pins[n] = pins[n];
  }
}

void RotarySwitch::init() {
  for (int n=0; n<8; n++) {
    pinMode(this->pins[n], INPUT_PULLUP);
  }
  this->last_mode = -1;
}

void RotarySwitch::read() {
  int is_pressed[8];
  for (int n=0; n<8; n++) {
    is_pressed[n] = !digitalRead(this->pins[n]);
  }

  if (is_pressed[0]) { 
    if (last_mode != 0) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode1Function) { this->onMode1Function(); }
    }
    last_mode = 0;
  } else if (is_pressed[1]) { 
    if (last_mode != 1) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode2Function) { this->onMode2Function(); }
    }
    last_mode = 1;
  } else if (is_pressed[2]) { 
    if (last_mode != 2) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode3Function) { this->onMode3Function(); }
    }
    last_mode = 2;
  } else if (is_pressed[3]) { 
    if (last_mode != 3) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode4Function) { this->onMode4Function(); }
    }
    last_mode = 3;
  } else if (is_pressed[4]) { 
    if (last_mode != 4) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode5Function) { this->onMode5Function(); }
    }
    last_mode = 4;
  } else if (is_pressed[5]) { 
    if (last_mode != 5) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode6Function) { this->onMode6Function(); }
    }
    last_mode = 5;
  } else if (is_pressed[6]) { 
    if (last_mode != 6) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode7Function) { this->onMode7Function(); }
    }
    last_mode = 6;
  } else if (is_pressed[7]) { 
    if (last_mode != 7) {
      if (this->onChangeFunction) { this->onChangeFunction(); }
      if (this->onMode8Function) { this->onMode8Function(); }
    }
    last_mode = 7;
  }
}

void RotarySwitch::onChange(RotarySwitchCallback f) {
  this->onChangeFunction = f;
}

void RotarySwitch::onMode1(RotarySwitchCallback f) {
  this->onMode1Function = f;
}
void RotarySwitch::onMode2(RotarySwitchCallback f) {
  this->onMode2Function = f;
}
void RotarySwitch::onMode3(RotarySwitchCallback f) {
  this->onMode3Function = f;
}
void RotarySwitch::onMode4(RotarySwitchCallback f) {
  this->onMode4Function = f;
}
void RotarySwitch::onMode5(RotarySwitchCallback f) {
  this->onMode5Function = f;
}
void RotarySwitch::onMode6(RotarySwitchCallback f) {
  this->onMode6Function = f;
}
void RotarySwitch::onMode7(RotarySwitchCallback f) {
  this->onMode7Function = f;
}
void RotarySwitch::onMode8(RotarySwitchCallback f) {
  this->onMode8Function = f;
}


#endif
