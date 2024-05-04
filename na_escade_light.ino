#include <FastLED.h>
#include "buttons.h"
#include "rotaryswitch.h"
#include "easer.h"

// How many leds in your strip?
#define NUM_LEDS 117
#define DATA_PIN 3

Button button = Button(12);
// Pins         Mode  1  2  3  4  5  6  7  8
int rotary_pins[8] = {8, 7, 6, 5, 4, 2, 9, 10};
RotarySwitch rotary = RotarySwitch(rotary_pins);
enum ColorMode {
  static_colors,
  animate_hue,
  moving_stripes,
  blinking,
  flashing,
};

uint8_t on_air = 0;

float on_air_variation, on_air_variation_goal = 0;
float on_air_hue, on_air_hue_goal = 0;
float on_air_hue_increment, on_air_hue_increment_goal = 0;
uint8_t on_air_sat, on_air_sat_goal = 255;
uint8_t on_air_brightness, on_air_brightness_goal = 0;
ColorMode on_air_color_mode = ColorMode::static_colors;
Easer on_air_hue_easer, on_air_hue_increment_easer, on_air_sat_easer, on_air_brightness_easer, on_air_variation_easer;

float color_variation = 1020;
float color_variation_goal = color_variation;
float color_hue, color_hue_goal = 0;
float color_hue_increment, color_hue_increment_goal = 1;
uint8_t color_sat, color_sat_goal = 255;
uint8_t color_brightness = 0;
uint8_t color_brightness_goal = 255;
ColorMode color_color_mode = ColorMode::animate_hue;
Easer color_hue_easer, color_hue_increment_easer, color_sat_easer, color_brightness_easer, color_variation_easer;

// Define the array of leds
CRGB leds[NUM_LEDS];

int span, j;
float x;


void toggle_on_air() {
  Serial.print("Toggle ");
  Serial.print(on_air);
  Serial.print(" -> ");
  if (on_air == 0) { on_air = 1; on_air_brightness_goal = 255; }
  else { on_air = 0; on_air_brightness_goal = 0; }
  Serial.println(on_air);
}

void mode1() {
  Serial.println("mode 1: Pink");
  color_hue_goal = 240;
  color_hue = color_hue_goal;
  color_variation_goal = 0;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = 0;
  color_hue_increment = 0;
  color_color_mode = ColorMode::static_colors;

  on_air_hue_goal = 0;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_hue_increment = 0;
  on_air_color_mode = ColorMode::static_colors;
}
void mode2() {
  Serial.println("mode 2: Sierra Gradient with Pink");
  color_hue_goal = 20;
  color_hue = color_hue_goal;
  color_variation_goal = 100;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = 0;
  color_hue_increment = 0;
  color_color_mode = ColorMode::static_colors;

  on_air_hue_goal = 240;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_hue_increment = 0;
  on_air_color_mode = ColorMode::static_colors;
}
void mode3() {
  Serial.println("mode 3: Total Pink");
  color_hue_goal = 240;
  color_hue = color_hue_goal;
  color_variation_goal = 0;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = 0;
  color_hue_increment = 0;
  color_color_mode = ColorMode::static_colors;

  on_air_hue_goal = 240;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_hue_increment = 0;
  on_air_color_mode = ColorMode::static_colors;
}
void mode4() {
  Serial.println("mode 4: White");
  color_hue_goal = 240;
  color_hue = color_hue_goal;
  color_variation_goal = 0;
  color_brightness_goal = 255;
  color_sat_goal = 0;
  color_hue_increment_goal = 0;
  color_hue_increment = 0;
  color_color_mode = ColorMode::static_colors;

  on_air_hue_goal = 0;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_hue_increment = 0;
  on_air_color_mode = ColorMode::static_colors;
}
void mode5() {
  Serial.println("mode 5: Wave");
  color_hue_goal = 240;
  color_hue = color_hue_goal;
  color_variation_goal = 10;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = 0.05;
  color_hue_increment = 0;
  color_color_mode = ColorMode::moving_stripes;

  on_air_hue_goal = 0;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_hue_increment = 0;
  on_air_color_mode = ColorMode::blinking;
}
void mode6() {
  Serial.println("mode 6: flashing");
  color_hue_goal = 240;
  color_hue = color_hue_goal;
  color_variation_goal = 10;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = 0.05;
  color_hue_increment = 0;
  color_color_mode = ColorMode::flashing;

  on_air_hue_goal = 0;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_hue_increment = 0;
  on_air_color_mode = ColorMode::blinking;
}
void mode7() {
  Serial.println("mode 7: Rainbow + RED");
  color_hue_goal = 0;
  color_hue = int(color_hue)%255;
  color_variation_goal = 720;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = 1;
  color_color_mode = ColorMode::animate_hue;

  on_air_hue_goal = 0;
  on_air_variation_goal = 0;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = 0;
  on_air_color_mode = ColorMode::static_colors;
}

void mode8() {
  Serial.println("mode 8: Slow Wide Rainbow");
  color_hue_goal = 0;
  color_hue = int(color_hue)%255;
  color_variation_goal = 120;
  color_brightness_goal = 255;
  color_sat_goal = 255;
  color_hue_increment_goal = -0.1;
  color_color_mode = ColorMode::animate_hue;

  on_air_hue_goal = 0;
  on_air_variation_goal = 120;
  on_air_brightness_goal = 255 * on_air;
  on_air_sat_goal = 255;
  on_air_hue_increment_goal = -0.1;
  on_air_color_mode = ColorMode::animate_hue;
}

void setup() {
  Serial.begin(9600);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    button.init();
    button.onPress(&toggle_on_air);
    rotary.init();
    rotary.onMode1(&mode1);
    rotary.onMode2(&mode2);
    rotary.onMode3(&mode3);
    rotary.onMode4(&mode4);
    rotary.onMode5(&mode5);
    rotary.onMode6(&mode6);
    rotary.onMode7(&mode7);
    rotary.onMode8(&mode8);
    Serial.println("Start");

    pinMode(2, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);

    on_air_hue_easer.setFactor(0.01);
    on_air_hue_increment_easer.setFactor(0.01);
    on_air_sat_easer.setFactor(0.01);
    on_air_brightness_easer.setFactor(0.01);
    on_air_variation_easer.setFactor(0.01);

    color_hue_easer.setFactor(0.01);
    color_hue_increment_easer.setFactor(0.01);
    color_sat_easer.setFactor(0.01);
    color_brightness_easer.setFactor(0.01);
    color_variation_easer.setFactor(0.01);
}

void loop() { 
  button.read();
  rotary.read();
  on_air_hue_increment = on_air_hue_increment_easer.Process(on_air_hue_increment_goal);
  on_air_sat = on_air_sat_easer.Process(on_air_sat_goal);
  on_air_brightness = on_air_brightness_easer.Process(on_air_brightness_goal);
  on_air_variation = on_air_variation_easer.Process(on_air_variation_goal);
  
  color_hue_increment = color_hue_increment_easer.Process(color_hue_increment_goal);
  color_sat = color_sat_easer.Process(color_sat_goal);
  color_brightness = color_brightness_easer.Process(color_brightness_goal);
  color_variation = color_variation_easer.Process(color_variation_goal);
  
  // Turn the LED on, then pause
  if (color_color_mode == ColorMode::animate_hue) {
    color_hue_goal += color_hue_increment;
  }
  color_hue = color_hue_easer.Process(color_hue_goal);

  if (on_air_color_mode == ColorMode::animate_hue) {
    on_air_hue_goal += on_air_hue_increment;
  }
  on_air_hue = on_air_hue_easer.Process(on_air_hue_goal);
  // Serial.print(color_hue);
  // Serial.print(" (Goal: ");
  // Serial.print(color_hue_goal);
  // Serial.println(")");

  // Serial.println();

  // ON AIR LEDS (bottom row)
  switch (on_air_color_mode) {
    case ColorMode::blinking:
      {
        Serial.println("Blinking");
        int brightness = int(on_air_brightness * min(1.0f, max(0.0f, 2*sin(millis()/500.0f))));
        span = 18;
        j = 0;
        for (uint8_t i=0; i<18; i++) {
          x = (1.0f/span) * j;
          j++;
          leds[i] = CHSV(int(x*on_air_variation + int(on_air_hue))%255, on_air_sat, brightness);
        }
        // ON AIR LEDS (top row)
        span = 18;
        j = 0;
        for (uint8_t i=35; i>=18; i--) {
          x = (1.0f/span) * j;
          j++;
          leds[i] = CHSV(int(x*on_air_variation + int(on_air_hue))%255, on_air_sat, brightness);
        }
      }
      break;
    default:
      {
        Serial.println("Default");
        span = 18;
        j = 0;
        for (uint8_t i=0; i<18; i++) {
          x = (1.0f/span) * j;
          j++;
          leds[i] = CHSV(int(x*on_air_variation + int(on_air_hue))%255, on_air_sat, on_air_brightness);
        }
        // ON AIR LEDS (top row)
        span = 18;
        j = 0;
        for (uint8_t i=35; i>=18; i--) {
          x = (1.0f/span) * j;
          j++;
          leds[i] = CHSV(int(x*on_air_variation + int(on_air_hue))%255, on_air_sat, on_air_brightness);
        }
      }
      break;
  }

  switch (color_color_mode) {
      case ColorMode::flashing:
      {
        // int brightness = int(color_brightness * abs(sin(millis()/2000.0f)));
        // Serial.println(brightness);
        // Rest of the Leds Left to Right (bottom row)
        float wave = 500.0f + sin( millis()/4000.0f) * 1000.0f;
        span = 73-36;
        j = 0;
        for (uint8_t i=36; i<73; i++) {
          x = (1.0f/span) * j;
          j++;
          int brightness = 0;
          if (random(1500) > wave) {
            brightness =  int(color_brightness * max(0.0f, sin(wave + x*4 - millis()/1000.0f)));
          }
          leds[i] = CHSV(int(x*color_variation + int(color_hue) + wave * -0.1f)%255, color_sat, brightness);
        }
        // Rest of the Leds Left to Right (top row)
        span = NUM_LEDS-1-73;
        j = 0;
        for (uint8_t i=NUM_LEDS-1; i>=73; i--) {
          x = (1.0f/span) * j;
          j++;
          int brightness = 0;
          if (random(1000) > wave) {
            brightness =  int(color_brightness * max(0.0f, sin(wave + x*4 - millis()/1000.0f)));
          }
          leds[i] = CHSV(int(x*color_variation + int(color_hue) + wave * -.1f)%255, color_sat, brightness);
        }
      }
      break;
     case ColorMode::moving_stripes:
      {
        // int brightness = int(color_brightness * abs(sin(millis()/2000.0f)));
        // Serial.println(brightness);
        // Rest of the Leds Left to Right (bottom row)
        float wave = 2.5f + sin( millis()/4000.0f) * 5.0f;
        span = 73-36;
        j = 0;
        for (uint8_t i=36; i<73; i++) {
          x = (1.0f/span) * j;
          j++;
          int brightness = int(color_brightness * max(0.0f, sin(wave + x*40 - millis()/1000.0f)));
          leds[i] = CHSV(int(x*color_variation + int(color_hue) + wave * -5.0f)%255, color_sat, brightness);
        }
        // Rest of the Leds Left to Right (top row)
        span = NUM_LEDS-1-73;
        j = 0;
        for (uint8_t i=NUM_LEDS-1; i>=73; i--) {
          x = (1.0f/span) * j;
          j++;
          int brightness = int(color_brightness * max(0.0f, sin(wave + x*40 - millis()/1000.0f)));
          leds[i] = CHSV(int(x*color_variation + int(color_hue) + wave * -5.0f)%255, color_sat, brightness);
        }
      }
      break;
    default:
      {
        Serial.println("Default happens still!");
        // Rest of the Leds Left to Right (bottom row)
        span = 73-36;
        j = 0;
        for (uint8_t i=36; i<73; i++) {
          x = (1.0f/span) * j;
          j++;
          leds[i] = CHSV(int(x*color_variation + int(color_hue))%255, color_sat, color_brightness);
        }
        // Rest of the Leds Left to Right (top row)
        span = NUM_LEDS-1-73;
        j = 0;
        for (uint8_t i=NUM_LEDS-1; i>=73; i--) {
          x = (1.0f/span) * j;
          j++;
          leds[i] = CHSV(int(x*color_variation + int(color_hue))%255, color_sat, color_brightness);
        }
      }
      break;
  }
  FastLED.show();
  delay(10);
  // Now turn the LED off, then pause
  // leds[0] = CRGB::Black;
  // leds[1] = CRGB::Black;
  // leds[2] = CRGB::Black;
  // FastLED.show();
  // delay(10);
}