# LightweightServo

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Commits since latest](https://img.shields.io/github/commits-since/ArminJo/LightweightServo/latest)](https://github.com/ArminJo/LightweightServo/commits/master)
[![Build Status](https://github.com/ArminJo/LightweightServo/workflows/LibraryBuild/badge.svg)](https://github.com/ArminJo/LightweightServo/actions)
![Hit Counter](https://visitor-badge.laobi.icu/badge?page_id=ArminJo_LightweightServo)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https://github.com/ArminJo/LightweightServo)](https://github.com/brentvollebregt/hit-counter)

### Included in the Arduino library [ServoEasing](https://github.com/ArminJo/ServoEasing)

## Small servo library for Arduino
This library is contained in the Arduino [SevoEasing](https://github.com/ArminJo/ServoEasing) library.
 *  comparable to [Adafruit_TiCoServo library](https://github.com/adafruit/Adafruit_TiCoServo)
 *  Enables use of NeoPixels and servos in the same Arduino sketch
 *  Lightweight Servo implementation only for pin 9 and 10.
 *  Only timer1 hardware and no interrupts or other overhead used.
 *  Provides auto initialization.
 *  Save up to 600 bytes code size / 40 bytes RAM including auto initialization compared to Arduino Servo library.
 *  8 bytes for each call to setLightweightServoPulse...

## Usage
As simple as this:
```
#include "LightweightServo.hpp"

void setup() {
    // no initialization required for LightweightServo :-)
    // or use manual initialization (and compiler macro "DISABLE_SERVO_TIMER_AUTO_INITIALIZE") to save additional 60 bytes program space
    // initLightweightServoPin9();
}

void loop() {
    write9(0);
    delay(1000);
    write9(180);
    delay(1000);
}
```

# [API](https://github.com/ArminJo/LightweightServo/blob/master/src/LightweightServo.h#L42)

# Compile options / macros for this library
To customize the software to save even more bytes, there are some compile options / macros available.<br/>
Modify it by commenting them out or in, or change the values if applicable. Or define the macro with the -D compiler option for global compile (the latter is not possible with the Arduino IDE, so consider using [Sloeber](https://eclipse.baeyens.it).<br/>
| Option | Default | File | Description |
|-|-|-|-|
| `DISABLE_SERVO_TIMER_AUTO_INITIALIZE` | disabled | LightweightServo.h | Saves up to 60 bytes flash memory. You must then use the init function `initLightweightServoPin9And10()` or `initLightweightServoPin9_10()` manually. |
