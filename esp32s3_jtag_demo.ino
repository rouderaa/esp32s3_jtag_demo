// ESP32-S3 WS2812 RGB LED Blink Program for JTAG Debugging Demo
// Using Adafruit NeoPixel library for WS2812 control
// Serial output on GPIO43 (TX) and GPIO44 (RX) - Hardware UART0

#include <Adafruit_NeoPixel.h>

#define LED_PIN 21       // WS2812 data pin
#define NUM_PIXELS 1     // Number of WS2812 LEDs
#define BLINK_DELAY 500  // milliseconds

// UART pins for Serial communication (use with USB-to-Serial adapter)
#define UART_TX 43
#define UART_RX 44

// Create NeoPixel object
Adafruit_NeoPixel strip(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Global variables for debugging inspection via JTAG
volatile int blinkCount = 0;
volatile unsigned long lastBlinkTime = 0;
volatile bool ledState = false;
volatile uint8_t currentRed = 0;
volatile uint8_t currentGreen = 0;
volatile uint8_t currentBlue = 0;

// Color definitions
const uint8_t COLOR_R = 0;  // Red component
const uint8_t COLOR_G = 50; // Green component
const uint8_t COLOR_B = 0;  // Blue component

void setup() {
  // Initialize hardware serial on GPIO43 (TX) and GPIO44 (RX)
  // Connect a USB-to-Serial adapter: TX->RX(44), RX->TX(43), GND->GND
  Serial.begin(115200, SERIAL_8N1, UART_RX, UART_TX);
  delay(1000);
  
  Serial.printf("ESP32-S3 WS2812 JTAG Blink Demo\r\n");
  Serial.printf("================================\r\n");
  Serial.printf("Serial: GPIO43 (TX), GPIO44 (RX)\r\n");
  Serial.printf("WS2812 Pin: GPIO%d\r\n", LED_PIN);
  Serial.printf("Number of LEDs: %d\r\n", NUM_PIXELS);
  Serial.printf("Blink Delay: %d ms\r\n", BLINK_DELAY);
  Serial.printf("Color: R=%d G=%d B=%d\r\n", COLOR_R, COLOR_G, COLOR_B);
  
  // Initialize WS2812
  strip.begin();
  strip.setBrightness(50);  // Set brightness (0-255)
  strip.show();  // Initialize all pixels to 'off'  
}

void loop() {
  // Toggle LED state
  ledState = !ledState;
  
  if (ledState) {
    // Turn LED on with specified color
    currentRed = COLOR_R;
    currentGreen = COLOR_G;
    currentBlue = COLOR_B;
    strip.setPixelColor(0, strip.Color(currentRed, currentGreen, currentBlue));
  } else {
    // Turn LED off
    currentRed = 0;
    currentGreen = 0;
    currentBlue = 0;
    strip.setPixelColor(0, strip.Color(0, 0, 0));
  }
  
  strip.show();  // Update the LED
  
  // Update tracking variables (useful for JTAG inspection)
  blinkCount++;
  lastBlinkTime = millis();
  
  // Print status
  Serial.printf("Blink #%d - LED %s (R:%d G:%d B:%d) at %lu ms\r\n", 
                blinkCount, 
                ledState ? "ON" : "OFF",
                currentRed, currentGreen, currentBlue,
                lastBlinkTime);
  
  // Delay
  delay(BLINK_DELAY);  
}
