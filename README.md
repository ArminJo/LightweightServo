# LightweightServo

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://travis-ci.org/ArminJo/LightweightServo.svg?branch=master)](https://travis-ci.org/ArminJo/LightweightServo)

## Small servo library for Arduino
 *  Lightweight Servo implementation only for pin 9 and 10.
 *  Only timer1 hardware and no interrupts or other overhead used.
 *  Provides auto initialization.
 *  300 bytes code size / 4 bytes RAM including auto initialization compared to 700 / 48 bytes for Arduino Servo library.
 *  8 bytes for each call to setLightweightServoPulse...

## Usage
As simple as this:
```
void setup() {
    // no initialization needed for LightweightServo :-)
}

void loop() {
    setLightweightServoPulsePin9(0);
    delay(1000);
    setLightweightServoPulsePin9(180);
    delay(1000);
}
```