/*
 * Setings file 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <avr/pgmspace.h>
#ifndef settings_h
#define settings_h

// #define Debug

// Choose the display you will be using
#define OLED_128x64_ADAFRUIT_SCREENS

// use the library from https://github.com/badzz/Adafruit_SH1106 before enabling
//#define SH1106

// u8glib has performance issues.
//#define OLED_128x64_U8G_SCREENS
 


//#define USE_FLIP_SCREEN
//js #define USE_BOOT_LOGO

// Choose if you wish to use 8 additional Channels 
// 5362 MHz 5399 MHz 5436 MHz 5473 MHz 5510 MHz 5547 MHz 5584 MHz 5621 MHz
// Local laws may prohibit the use of these frequencies use at your own risk!
//#define USE_LBAND

 
#define spiDataPin 10
#define slaveSelectPin 11
#define spiClockPin 12

// buzzer PIN
#define BUZ_PIN 3
// encoder
#define ENCODER_A_PIN 6 // ec11 encoder A-pin ( ausserdem C-pin gelb und D-button-pin gelb auf graound) blau
#define ENCODER_B_PIN 5 // ec11 encoder B-pin rot
#define ENCODER_BTN_PIN 8 // ec11 encoder E-button-pin gruen


    #define CHANNEL_MAX_INDEX 39


    #define MIN_TUNE_TIME 35

    #define CHANNEL_MAX 39

#define CHANNEL_MIN 0

#define MHZ_RANGE_MIN 5505 // 5645
#define MHZ_RANGE_MAX 5995 // 5945

#define MHZ_START 5765



#endif // file_defined
