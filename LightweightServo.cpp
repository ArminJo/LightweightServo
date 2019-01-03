/*
 *  LightweightServo.cpp
 *
 *  Lightweight Servo implementation only for pin 9 and 10 using only timer1 hardware and no interrupts or other overhead.
 *  Provides auto initialization.
 *  300 bytes code size / 4 bytes RAM including auto initialization compared to 700 / 48 bytes for Arduino Servo library.
 *  8 bytes for each call to setLightweightServoPulse...
 *
 *  Copyright (C) 2019  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#include <Arduino.h>
#include <LightweightServo.h>

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
//#define DISABLE_SERVO_TIMER_AUTO_INITIALIZE // outcommenting this saves 70 bytes flash memory if you use the init function initLightweightServoPin9And10() manually.

#define COUNT_FOR_20_MILLIS 40000 // you can modify this if you have servos which accept a higher rate

/*
 * Variables to enable adjustment for different servo types
 * Resolution is 1/2 microseconds, so values are twice the microseconds!!!
 * 1088 and 4800 are values compatible with standard arduino values
 * 4 bytes RAM compared to 48 bytes for standard Arduino library
 */
int sServoPulseWidthFor0Degree = 1088;
int sServoPulseWidthFor180Degree = 4800;

/*
 * Use 16 bit timer1 for generating 2 servo signals entirely by hardware without any interrupts.
 * Use FastPWM mode and generate pulse at start of the 20ms period
 * The 2 servo signals are tied to pin 9 and 10 of an 328.
 * Attention - both pins are set to OUTPUT here!
 * 32 bytes code size
 */
void initLightweightServoPin9And10() {
    /*
     * Periods below 20 ms gives problems with long signals i.e. the positioning is not possible
     */
    DDRB |= _BV(DDB1) | _BV(DDB2);                // set pins OC1A = PortB1 -> PIN 9 and OC1B = PortB2 -> PIN 10 to output direction
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11); // FastPWM Mode mode TOP (20ms) determined by ICR1 - non-inverting Compare Output mode OC1A+OC1B
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);    // set prescaler to 8, FastPWM mode mode bits WGM13 + WGM12
    ICR1 = COUNT_FOR_20_MILLIS;  // set period to 20 ms
    // do not set counter here, since with counter = 0 (default) no output signal is generated.
}

/*
 * Use 16 bit timer1 for generating 2 servo signals entirely by hardware without any interrupts.
 * Use FastPWM mode and generate pulse at start of the 20ms period
 * The 2 servo signals are tied to pin 9 and 10 of an 328.
 * Attention - the selected pin is set to OUTPUT here!
 * 54 bytes code size
 */
void initLightweightServoPin9_10(bool aUsePin9, bool aUsePin10) {
    /*
     * Periods below 20 ms may give problems with long signals i.e. the positioning is not possible
     */
    uint8_t tNewTCCR1A = TCCR1A & (_BV(COM1A1) | _BV(COM1B1)); // keep existing channel settings
    tNewTCCR1A |= _BV(WGM11); // FastPWM Mode mode TOP (20ms) determined by ICR1

    if (aUsePin9) {
        DDRB |= _BV(DDB1);   // set OC1A = PortB1 -> PIN 9 to output direction
        tNewTCCR1A |= _BV(COM1A1); // non-inverting Compare Output mode OC1A
    }
    if (aUsePin10) {
        DDRB |= _BV(DDB2);   // set OC1B = PortB2 -> PIN 10 to output direction
        tNewTCCR1A |= _BV(COM1B1); // non-inverting Compare Output mode OC1B
    }
    TCCR1A = tNewTCCR1A;
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11);    // set prescaler to 8, FastPWM Mode mode bits WGM13 + WGM12
    ICR1 = COUNT_FOR_20_MILLIS;  // set period to 20 ms
    // do not set counter here, since with counter = 0 (default) no output signal is generated.
}

/*
 * If value is below 180 then assume degree, otherwise assume microseconds
 * If aUpdateFast then enable starting a new output pulse if more than 5 ms since last one, some servo might react faster in this mode.
 * If aUsePin9 is false, then Pin10 is used
 * 236 / 186(without auto init) bytes code size
 */
void setLightweightServoPulse(int aValue, bool aUsePin9, bool aUpdateFast) {
#ifndef DISABLE_SERVO_TIMER_AUTO_INITIALIZE
    // auto initialize
    if ((TCCR1B != (_BV(WGM13) | _BV(WGM12) | _BV(CS11))) || (aUsePin9 && ((TCCR1A & ~_BV(COM1B1)) != (_BV(COM1A1) | _BV(WGM11))))
            || (!aUsePin9 && ((TCCR1A & ~_BV(COM1A1)) != (_BV(COM1B1) | _BV(WGM11))))) {
        initLightweightServoPin9_10(aUsePin9, !aUsePin9);
    }
#endif
    if (aValue <= 180) {
        aValue = map(aValue, 0, 180, sServoPulseWidthFor0Degree, sServoPulseWidthFor180Degree);
    } else {
// since the resolution is 1/2 of microsecond
        aValue *= 2;
    }
    if (aUpdateFast) {
        uint16_t tTimerCount = TCNT1;
        if (tTimerCount > 10000) {
            // more than 5 ms since last pulse -> start a new one
            TCNT1 = COUNT_FOR_20_MILLIS - 1;
        }
    }
    if (aUsePin9) {
        OCR1A = aValue;
    } else {
        OCR1B = aValue;
    }
}

/*
 * Set the mapping pulse width values for 0 and 180 degree
 */
void setLightweightServoPulseMicrosFor0And180Degree(int a0DegreeValue, int a180DegreeValue) {
// *2 since internal values are meant for the 1/2 microseconds resolution of timer
    sServoPulseWidthFor0Degree = a0DegreeValue * 2;
    sServoPulseWidthFor180Degree = a180DegreeValue * 2;
}

/*
 * Pin 9 / Channel A. If value is below 180 then assume degree, otherwise assume microseconds
 */
void setLightweightServoPulsePin9(int aValue, bool aUpdateFast) {
    setLightweightServoPulse(aValue, true, aUpdateFast);
}

/*
 * Pin 10 / Channel B
 */
void setLightweightServoPulsePin10(int aValue, bool aUpdateFast) {
    setLightweightServoPulse(aValue, false, aUpdateFast);
}

int getMicrosFromDegree(int aValueDegree) {
    // sServoPulseWidth... has a resolution of 1/2 microsecond
    return (map(aValueDegree, 0, 180, sServoPulseWidthFor0Degree, sServoPulseWidthFor180Degree) / 2);
}

int getDegreeFromMicros(int aValueMicros) {
    // sServoPulseWidth... has a resolution of 1/2 microsecond
    return map((aValueMicros * 2), sServoPulseWidthFor0Degree, sServoPulseWidthFor180Degree, 0, 180);
}

#endif

