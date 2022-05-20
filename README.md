# LightweightServo

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Commits since latest](https://img.shields.io/github/commits-since/ArminJo/LightweightServo/latest)](https://github.com/ArminJo/LightweightServo/commits/master)
[![Build Status](https://github.com/ArminJo/LightweightServo/workflows/LibraryBuild/badge.svg)](https://github.com/ArminJo/LightweightServo/actions)
![Hit Counter](https://visitor-badge.laobi.icu/badge?page_id=ArminJo_LightweightServo)


### Included in the Arduino library [ServoEasing](https://github.com/ArminJo/ServoEasing)

## Small servo library for Arduino
This library is contained in the Arduino [SevoEasing](https://github.com/ArminJo/ServoEasing) library.
 *  Comparable to [Adafruit_TiCoServo library](https://github.com/adafruit/Adafruit_TiCoServo).
 *  No problems with **servo twitching**.
 *  Enables use of NeoPixels, SoftwareSerial, and DmxSimple together with servos in the same Arduino sketch.
 *  LightweightServo implementation **only for pin 9 and 10** of Arduino UNO, Nano etc..
 *  Only timer1 hardware and **no interrupts or other overhead** used.
 *  Provides **auto initialization**.
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
|-|-|-|-|
| `DISABLE_SERVO_TIMER_AUTO_INITIALIZE` | disabled | Saves up to 60 bytes flash memory. You must then use the init function `initLightweightServoPin9And10()` or `initLightweightServoPin9_10()` manually. |

### Changing include (*.h) files with Arduino IDE
First, use *Sketch > Show Sketch Folder (Ctrl+K)*.<br/>
If you have not yet saved the example as your own sketch, then you are instantly in the right library folder.<br/>
Otherwise you have to navigate to the parallel `libraries` folder and select the library you want to access.<br/>
In both cases the library source and include files are located in the libraries `src` directory.<br/>
The modification must be renewed for each new library version!

### Modifying compile options / macros with PlatformIO
If you are using PlatformIO, you can define the macros in the *[platformio.ini](https://docs.platformio.org/en/latest/projectconf/section_env_build.html)* file with `build_flags = -D MACRO_NAME` or `build_flags = -D MACRO_NAME=macroValue`.

### Modifying compile options / macros with Sloeber IDE
If you are using [Sloeber](https://eclipse.baeyens.it) as your IDE, you can easily define global symbols with *Properties > Arduino > CompileOptions*.<br/>
![Sloeber settings](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/pictures/SloeberDefineSymbols.png)

