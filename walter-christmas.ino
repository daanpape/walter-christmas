#include <FastLED.h>

/**
 * @brief The number of connected LEDs.
 */
#define NUM_LEDS 200

/**
 * @brief The data pin on which the LEDs are connected.
 */
#define DATA_PIN 10

/**
 * @brief The number of lights in a single section that lights up.
 */
#define SECTION_SIZE 10

/**
 * @brief The array of WS2812B LEDs.
 */
CRGB leds[NUM_LEDS];

/**
 * @brief The cursor of where we are lighting up the section.
 */
int cursor = SECTION_SIZE;

/**
 * @brief The direction in which the light runs.
 */
bool direction = true;

/**
 * @brief The current RED channel color.
 */
uint8_t red = 0;

/**
 * @brief The current GREEN channel color.
 */
uint8_t green = 0;

/**
 * @brief The current BLUE channel color.
 */
uint8_t blue = 255;

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

  for(int i = 0; i < SECTION_SIZE; ++i) {
    leds[cursor - i] = CRGB(red, green, blue);
  }
  
  FastLED.show();

  if(direction) {
    cursor += 1;
    if(cursor == NUM_LEDS) {
      direction = false;
      cursor = NUM_LEDS - 1;
      red = random(0, 256);
      green = random(0, 256);
      blue = random(0, 256);
      Serial.printf("New color: (%d, %d, %d)\n", (int) red, (int) green, (int) blue);
    }
  } else {
    cursor -= 1;

    if(cursor == SECTION_SIZE - 1) {
      direction = true;
      cursor = SECTION_SIZE;
      red = random(0, 256);
      green = random(0, 256);
      blue = random(0, 256);
      Serial.printf("New color: (%d, %d, %d)\n", (int) red, (int) green, (int) blue);
    }
  }
  
  delay(20);
}
