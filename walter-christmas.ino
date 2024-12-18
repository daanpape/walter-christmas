#include <FastLED.h>

/**
 * @brief LED Configuration
 */
#define NUM_LEDS 200      // Total number of LEDs
#define DATA_PIN 10       // Data pin for the LED strip
#define DELAY_MS 20       // Delay time for color fading
#define NUM_TWINKLES 5    // Number of twinkling LEDs
#define TWINKLE_TIME 100  // Duration (in ms) for a twinkle effect

/**
 * @brief LED array and color fading variables
 */
CRGB leds[NUM_LEDS];
CRGB currentColor = CRGB::Red;     // Start color
CRGB targetColor = CRGB::Blue;     // Next color to fade to
float fadeStep = 0.01;             // Step size for color blending

/**
 * @brief Twinkling LED Data
 */
struct Twinkle {
  int position;        // LED position
  uint32_t startTime;  // Time when twinkle started
  bool active;         // Is the twinkle currently active?
};

Twinkle twinkles[NUM_TWINKLES];  // Array of twinkling LEDs

void setup() {
  Serial.begin(115200);
  delay(2000); // Short startup delay
  Serial.println("Walter Christmas Lights v0.2 - Fading & Twinkle");

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();

  // Initialize twinkle array
  for (int i = 0; i < NUM_TWINKLES; ++i) {
    twinkles[i].active = false;
  }

  targetColor = getRandomColor();
}

void loop() {
  static float progress = 0.0; // Tracks progress of fading

  // Update fading background
  updateFadingBackground(&progress);

  // Handle twinkling LEDs
  handleTwinkles();

  FastLED.show();
  delay(DELAY_MS);
}

/**
 * @brief Smoothly fades all LEDs from currentColor to targetColor
 */
void updateFadingBackground(float *progress) {
  *progress += fadeStep; // Increment the fade progress
  if (*progress >= 1.0) {
    *progress = 0.0; // Reset progress
    currentColor = targetColor; // End the fade with the target color
    targetColor = getRandomColor(); // Pick a new target color
  }

  // Interpolate between currentColor and targetColor
  CRGB blendedColor = blend(currentColor, targetColor, *progress * 255);
  fill_solid(leds, NUM_LEDS, blendedColor);
}

/**
 * @brief Handle the random twinkling effect
 */
void handleTwinkles() {
  uint32_t currentTime = millis();

  // Activate new twinkles if available
  for (int i = 0; i < NUM_TWINKLES; ++i) {
    if (!twinkles[i].active) {
      twinkles[i].position = random(0, NUM_LEDS);  // Random LED position
      twinkles[i].startTime = currentTime;         // Mark start time
      twinkles[i].active = true;
      leds[twinkles[i].position] = CRGB::White;    // Bright white twinkle
    }
  }

  // Check and deactivate old twinkles
  for (int i = 0; i < NUM_TWINKLES; ++i) {
    if (twinkles[i].active && (currentTime - twinkles[i].startTime > TWINKLE_TIME)) {
      twinkles[i].active = false;  // Deactivate twinkle
    }
  }
}

/**
 * @brief Returns a random CRGB color with at least one channel active
 */
CRGB getRandomColor() {
  // Generate a random hue value (0-255)
  uint8_t hue = random(0, 256);

  // Convert from HSV to RGB, keeping the saturation at 100% and value at 40% (0.4)
  CHSV hsvColor = CHSV(hue, 255, 255 * 0.4);  // 40% brightness

  // Convert from CHSV to CRGB
  CRGB color = hsvColor;

  return color;
}