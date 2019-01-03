/*
 * LightweightServo.h
 *
 *  Created on: 02.01.2019
 *  Copyright (C) 2019  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 */

#include <stdint.h>

#ifndef LIGHTWEIGHT_SERVO_H_
#define LIGHTWEIGHT_SERVO_H_

/*
 * Lightweight servo library
 * Uses timer1 and Pin 9 + 10 as output
 */
void initLightweightServoPin9And10();
void initLightweightServoPin9_10(bool aUsePin9 = true, bool aUsePin10 = true);
void setLightweightServoPulseMicrosFor0And180Degree(int a0DegreeValue, int a180DegreeValue);
void setLightweightServoPulse(int aValue, bool aUsePin9, bool aUpdateFast = false);
void setLightweightServoPulsePin9(int aValue, bool aUpdateFast = false); // Channel A
void setLightweightServoPulsePin10(int aValue, bool aUpdateFast = false); // Channel B

// convenience functions
int getMicrosFromDegree(int aValueDegree);
int getDegreeFromMicros(int aValueMicros);

#endif // LIGHTWEIGHT_SERVO_H_
