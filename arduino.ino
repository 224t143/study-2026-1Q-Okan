#include <FastLED.h>

#define LED_PIN 6
#define NUM_LEDS 180

CRGB leds[NUM_LEDS];

int brightness = 40;
int blurAmount = 100;
int flowSpeed = 90;
int timeValue = 140;
int stability = 200;
int sharpness = 180;

int position = 0;
unsigned long lastMove = 0;

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);

  FastLED.clear();
  FastLED.show();
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');

    sscanf(data.c_str(), "%d,%d,%d,%d,%d,%d",
           &brightness,
           &blurAmount,
           &flowSpeed,
           &timeValue,
           &stability,
           &sharpness);
  }

  int safeBrightness = constrain(brightness, 1, 50);
  int interval = map(flowSpeed, 0, 255, 180, 25);
  int fadeAmount = map(blurAmount, 0, 255, 160, 40);
  int whitePower = constrain(sharpness, 10, 120);

  if (millis() - lastMove > interval) {
    lastMove = millis();

    fadeToBlackBy(leds, NUM_LEDS, fadeAmount);
    FastLED.setBrightness(safeBrightness);

    leds[position] = CRGB(whitePower, whitePower, whitePower);

    FastLED.show();

    position++;
    if (position >= NUM_LEDS) {
      position = 0;
    }
  }
}