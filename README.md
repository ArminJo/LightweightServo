<div align = center>

# [LightweightServo](https://github.com/ArminJo/LightweightServo)

[![Badge License: GPLv3](https://img.shields.io/badge/License-GPLv3-brightgreen.svg)](https://www.gnu.org/licenses/gpl-3.0)
 &nbsp; &nbsp;
[![Badge Version](https://img.shields.io/github/v/release/ArminJo/LightweightServo?include_prereleases&color=yellow&logo=DocuSign&logoColor=white)](https://github.com/ArminJo/LightweightServo/releases/latest)
 &nbsp; &nbsp;
[![Badge Commits since latest](https://img.shields.io/github/commits-since/ArminJo/LightweightServo/latest?color=yellow)](https://github.com/ArminJo/LightweightServo/commits/master)
 &nbsp; &nbsp;
[![Badge Build Status](https://github.com/ArminJo/LightweightServo/workflows/LibraryBuild/badge.svg)](https://github.com/ArminJo/LightweightServo/actions)
 &nbsp; &nbsp;
![Badge Hit Counter](https://visitor-badge.laobi.icu/badge?page_id=ArminJo_LightweightServo)
<br/>
<br/>
[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/badges/StandWithUkraine.svg)](https://stand-with-ukraine.pp.ua)

Part of the Arduino library [ServoEasing](https://github.com/ArminJo/ServoEasing)

[![Button Changelog](https://img.shields.io/badge/Changelog-blue?logoColor=white&logo=AzureArtifacts)](https://github.com/ArminJo/LightweightServo?tab=readme-ov-file#revision-history)

</div>

#### If you find this library useful, please give it a star.

&#x1F30E; [Google Translate](https://translate.google.com/translate?sl=en&u=https://github.com/ArminJo/LightweightServo)

## Small servo library for Arduino
This library is contained in the Arduino [SevoEasing](https://github.com/ArminJo/ServoEasing) library.
 *  Comparable to [Adafruit_TiCoServo library](https://github.com/adafruit/Adafruit_TiCoServo).
 *  No problems with **servo twitching**.
 *  Enables use of NeoPixels, SoftwareSerial, and DmxSimple together with servos in the same Arduino sketch.
 *  LightweightServo implementation **only for pin 9 and 10** of Arduino Uno, Nano etc..
 *  Only timer1 hardware and **no interrupts or other overhead** used.
 *  Provides **auto initialization**.
 *  Supports F_CPU of 16, 8, 4, 2, 1 MHz.
 *  **Save up to 600 bytes program size** / 40 bytes RAM including auto initialization compared to Arduino Servo library.
 *  8 bytes for each call to `write9()` or `write10()`.

## Usage
As simple as this:

```c++
#include "LightweightServo.hpp"

void setup() {
    // no initialization required for LightweightServo :-)
    // or use manual initialization (and compiler macro "DISABLE_SERVO_TIMER_AUTO_INITIALIZE") to save additional 60 bytes program memory
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
To customize the library to different requirements, there are some compile options / macros available.<br/>
Most macros must be defined in your program before the line `#include <LightweightServo.hpp>` to take effect.<br/>
Modify them by enabling / disabling them, or change the values if applicable.

| Name | Default value | Description |
|-|-:|-|
| `DISABLE_SERVO_TIMER_AUTO_INITIALIZE` | disabled | Saves up to 60 bytes flash memory. You must then use the init function `initLightweightServoPin9And10()` or `initLightweightServoPin9_10()` manually. |
