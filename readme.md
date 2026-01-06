# ESP32-S3 WS2812 JTAG Blink Demo

A simple Arduino example for the **ESP32-S3** that blinks a **WS2812 (NeoPixel) RGB LED** while exposing internal state for **JTAG debugging**. The sketch also outputs status messages over a hardware UART.

This project is intended as a **bring-up and debugging demo** and works with **Arduino ESP32 core v2.3.7+**, which provides **automatic USB JTAG support** with no manual configuration.

---

## Features

- WS2812 / NeoPixel control using the **Adafruit NeoPixel** library
- Single RGB LED blink with configurable color and delay
- Hardware serial output on custom GPIO pins
- Global `volatile` variables for easy inspection via **JTAG**
- No external JTAG adapter required on ESP32-S3
- Uses a single USB cable for flashing, serial, and debugging

---

## Hardware Requirements

- ESP32-S3 development board (USB capable)
- WS2812 / NeoPixel RGB LED
- USB cable
- Optional USB-to-Serial adapter (for GPIO43/44 UART output)

---

## Pin Configuration

| Function        | GPIO |
|-----------------|------|
| WS2812 Data     | 21   |
| UART TX         | 43   |
| UART RX         | 44   |

### UART Wiring (Optional)

- Adapter TX → GPIO44  
- Adapter RX → GPIO43  
- GND → GND  

---

## LED Behavior

- The LED toggles **ON / OFF every 500 ms**
- Color is set to **Green (R=0, G=50, B=0)**
- Brightness is limited to reduce power draw but can go up to 255.
- Blink timing and state are observable via JTAG

---

## Serial Output

Serial output runs at **115200 baud** and includes:

- Blink count
- LED state (ON / OFF)
- RGB values
- Timestamp in milliseconds

---

## Dependencies

- [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)

Install via the Arduino Library Manager.

---

## Compiling and Uploading with Arduino IDE

### 1. Install Arduino IDE
- Download and install **Arduino IDE 2.x**

### 2. Add ESP32 Boards Manager URL
1. Open **File → Preferences**
2. In **Additional Boards Manager URLs**, add:

https://espressif.github.io/arduino-esp32/package_esp32_index.json

3. Click **OK**

> If other URLs already exist, separate entries with commas.

### 3. Install ESP32 Board Support
1. Open **Tools → Board → Boards Manager**
2. Search for **ESP32**
3. Install **“esp32 by Espressif Systems”**
- Version **2.3.7 or newer** is required

### 4. Select Board and Tool Options
- **Tools → Board:** `ESP32S3 Dev Module`

### 5. Install Required Library
1. Open **Sketch → Include Library → Manage Libraries**
2. Search for **Adafruit NeoPixel**
3. Install the latest version

### 6. Compile and Upload
1. Connect the ESP32-S3 via USB
2. Select the correct **Port** under **Tools → Port**
   (on linux: /dev/ttyACM0)
3. Click **Upload**
4. To see the serial message use an terminal program like minicom (on linux).
   Set this program to /dev/ttyUSB0. This is a different serial port than
   used for debugging and uploading !
5. Observe LED blinking and serial messages

> If upload fails, press and hold the **BOOT** button while uploading.

---

## Using JTAG Debugging (ESP32-S3)

With **Arduino ESP32 core v2.3.7+**, the ESP32-S3 provides **USB JTAG automatically**.

### Key Characteristics

- No OpenOCD installation required
- No JTAG pin wiring required
- No configuration files required
- Uses the ESP32-S3 built-in USB JTAG interface

### Typical Debug Workflow

1. Upload the sketch in the Arduino ide (arrow icon at the top left)
2. Start a debug session from your IDE or debugger (triangle icont at the top left)
3. Set breakpoints in `loop()` by clicking the left margin of the program text.
4. Watch variables update as the LED toggles
5. Halt, step, or resume execution as needed

> The blinking LED makes it easy to confirm whether execution is running or halted.

---

## Notes

- Variables are declared `volatile` to prevent compiler optimization
- Ideal for stepping, breakpoints, and live variable inspection
- External JTAG probes are **not required** for ESP32-S3
- Designed for hardware bring-up and debug demonstrations

---

## License

MIT License
