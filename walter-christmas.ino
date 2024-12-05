#include <FastLED.h>

/**
 * @brief The number of connected LEDs.
 */
#define NUM_LEDS 100

/**
 * @brief The data pin on which the LEDs are connected.
 */
#define DATA_PIN 10

/**
 * @brief The array of WS2812B LEDs.
 */
CRGB leds[NUM_LEDS];

int cursor = 0;

void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("Walter Christmas Lights v0.0.1");

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  for(int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB(0,0,0);
  }

  leds[cursor] = CRGB(255,255,255);
  leds[cursor + 1] = CRGB(255,0,0);
  leds[cursor + 2] = CRGB(0,255,0);
  leds[cursor + 3] = CRGB(0,0,255);
  FastLED.show();

  cursor += 1;
  delay(100);
}
