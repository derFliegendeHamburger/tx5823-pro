/*
   OLED Screens by Shea Ivey
 
  The MIT License (MIT)
 
  Copyright (c) 2015 Shea Ivey
  **MODS Geroge chatzisavvidis
  
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
 
#include "settings.h"
#include <avr/pgmspace.h>
#ifdef OLED_128x64_ADAFRUIT_SCREENS
#include "screens.h" // function headers
 
#include "Adafruit_SSD1306.h"
 
#include "Adafruit_GFX.h"
#include <Wire.h>
#include <SPI.h>

 
// New version of PSTR that uses a temp buffer and returns char *
// by Shea Ivey
#define PSTR2(x) PSTRtoBuffer_P(PSTR(x))
char PSTR2_BUFFER[30]; // adjust size depending on need.
char *PSTRtoBuffer_P(PGM_P str)
{
  uint8_t c = '\0', i = 0;
  for (; (c = pgm_read_byte(str)) && i < sizeof(PSTR2_BUFFER); str++, i++) PSTR2_BUFFER[i] = c;
  PSTR2_BUFFER[i] = c;
  return PSTR2_BUFFER;
}
 
#define INVERT INVERSE
#define OLED_RESET 4
#ifdef SH1106
Adafruit_SH1106 display(OLED_RESET);
#if !defined SH1106_128_64
#error("Screen size incorrect, please fix Adafruit_SH1106.h!");
#endif
#else
Adafruit_SSD1306 display(OLED_RESET);
#if !defined SSD1306_128_64
#error("Screen size incorrect, please fix Adafruit_SSD1306.h!");
#endif
#endif


extern uint8_t system_state;

 
screens::screens()
{
  last_channel = -1;

}
 
char screens::begin(const char *call_sign)
{
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D or 0x3C (for the 128x64)
 
 
#ifdef USE_FLIP_SCREEN
  flip();
#endif
 
#ifdef USE_BOOT_LOGO
  display.display(); // show splash screen
  delay(2000);
#endif
  // init done
  reset();
 
  return 0; // no errors
}
 
void screens::reset()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}
 
void screens::flip()
{
  display.setRotation(2);
}
 
void screens::drawTitleBox(const char *title, bool centerFlag)
{
  display.drawRect(0, 0, display.width(), display.height(), WHITE);
  display.fillRect(0, 0, display.width(), 11, WHITE);
 
  display.setTextSize(1);
  display.setTextColor(BLACK);

  if (centerFlag)
    display.setCursor(((display.width() - (strlen(title) * 6)) / 2), 2);
  else
    display.setCursor(2, 2);

  display.print(title);
  
  display.setTextColor(WHITE);
}


void screens::splash( const char *version, const char *call_sign)
{
  reset();
//  display.setTextSize(6);
//  display.setTextColor(WHITE);
//  display.setCursor(0, 0);
//  display.print(channelName, HEX);
//  display.setTextSize(1);
//  display.setCursor(70, 0);
//  display.print(call_sign);
//  display.setTextSize(2);
//  display.setCursor(70, 28);
//  display.setTextColor(WHITE);
//  display.print(channelFrequency);
//  display.setTextSize(1);

  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(2, 0);
  display.print(version);
  display.setTextSize(2);
  display.setCursor(0, 44);
  display.print(call_sign);
  display.setTextSize(2);
  display.display();
}
 
void screens::movingFreq( uint16_t channelFrequency)
{
  reset();
//  display.setTextSize(6);
//  display.setTextColor(WHITE);
//  display.setCursor(0, 0);
//  display.print(channelName, HEX);
//  display.setTextSize(1);
//  display.setCursor(70, 0);
//  display.print(call_sign);
//  display.setTextSize(2);
//  display.setCursor(70, 28);
//  display.setTextColor(WHITE);
//  display.print(channelFrequency);
//  display.setTextSize(1);

  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(2, 15);
  display.print(channelFrequency);
  display.display();
}


void screens::screenSaver( uint16_t channelFrequency, const char *call_sign)
{
  reset();
//  display.setTextSize(6);
//  display.setTextColor(WHITE);
//  display.setCursor(0, 0);
//  display.print(channelName, HEX);
//  display.setTextSize(1);
//  display.setCursor(70, 0);
//  display.print(call_sign);
//  display.setTextSize(2);
//  display.setCursor(70, 28);
//  display.setTextColor(WHITE);
//  display.print(channelFrequency);
//  display.setTextSize(1);
 
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(2, 0);
  display.print(channelFrequency);
  display.setTextSize(2);
  display.setCursor(0, 44);
  display.print(call_sign);
  display.display();
}
 
 
#endif
