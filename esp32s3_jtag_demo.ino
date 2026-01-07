// ESP32-S3 WS2812 RGB LED Blink Example
#include <Adafruit_NeoPixel.h>

#define LED_PIN 21
#define NUM_PIXELS 1

Adafruit_NeoPixel colorLed(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

bool ledState = false;

void setup() {
  Serial.begin(115200);
  
  colorLed.begin();
  colorLed.setBrightness(50);
  colorLed.show();
  
  Serial.println("WS2812 Blink Demo Started");
}

void loop() {
  ledState = !ledState;
  
  if (ledState) {
    colorLed.setPixelColor(0, colorLed.Color(0, 50, 0));  // Green
    Serial.println("LED GREEN");
  } else {
    colorLed.setPixelColor(0, colorLed.Color(50, 0, 0));  // Red
    Serial.println("LED RED");
  }
  
  colorLed.show();
  
  delay(500);
}
