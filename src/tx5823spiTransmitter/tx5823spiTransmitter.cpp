/*
   SPI driver based on fs_skyrf_58g-main.c Written by Simon Chambers
   TVOUT by Myles Metzel
   Scanner by Johan Hermen
   Initial 2 Button version by Peter (pete1990)
   Refactored and GUI reworked by Marko Hoepken
   Universal version my Marko Hoepken
   Diversity Receiver Mode and GUI improvements by Shea Ivey
   OLED Version by Shea Ivey
   Separating display concerns by Shea Ivey
   10 Favorite channels and functionality by George Chatzisavvidis
   change in displays by George Chatzisavvidis
   Adding Fatshark button to work with the module by George Chatzisavvidis
   OSD SUPPORT George Chatzisavvidis

   RX5808_etheli v1.0 version (by ET http://www.etheli.com):
     Implemented frequency set BY-MHZ MODE
     Renamed 'C' and 'D' band names to 'R' and 'L'
     Various code and functionality improvements

  --------------------------------------------------------------------------

  The MIT License (MIT)

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

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "settings.h"


// uncomment depending on the display you are using.
// this is an issue with the arduino preprocessor

#ifdef OLED_128x64_ADAFRUIT_SCREENS

#ifdef SH1106
// #include "Adafruit_SH1106.h"
#else
#include "Adafruit_SSD1306.h"
#endif
#include "Adafruit_GFX.h"
#include <Wire.h>
#include <SPI.h>
#endif

#include "ClickEncoder.h"
#include <Ticker.h>

#include "screens.h"
screens drawScreen;


static char version[20] = "v1.0d";
static char call_sign[20] = "5823spiTX";


static uint16_t nextfreq = MHZ_START; // what is the moving value from encoder rotation
static uint16_t freq = 0; // what the TX is currently tuned to
static uint16_t dispfreq = 0; // what is being displayed


// ------------------ declarations ------------------------

void call_encoder_service();
void updateDisplay();
void updateFreqAndDisplay();
void setup();
void loop();

ClickEncoder *encoder;
int16_t encoder_value = 0;
ClickEncoder::Button encoder_button = encoder->getButton();

Ticker ticker1(updateDisplay,100,0,MILLIS);
Ticker ticker2(call_encoder_service,1,0,MILLIS);

//----------------------------------------------------------------------------------
void call_encoder_service()
{
  //LOCK = true;
  encoder->service();
  //LOCK = false;
  //updateDisplay();
}
//----------------------------------------------------------------------------------
#define BUZ_ON   digitalWrite(BUZ_PIN, HIGH);
#define BUZ_OFF  digitalWrite(BUZ_PIN, LOW);
//#define BUZ_ON   {PORTB |= _BV(5);}
//#define BUZ_OFF  {PORTB &= ~_BV(5);}
#define BUZ_TICK 1
#define BUZ_CLICK 5

void buzz(int n) {
  BUZ_ON;
  delay(n);
  BUZ_OFF
}
void fanfare(uint8_t max) {
  for (uint8_t i=1; i < max; i++) {buzz(i); delay(5*max -i*3); }
}
//----------------------------------------------------------------------------------
/*
 * execute a complete SPI write operation
 */
void spi_write(uint8_t addr, uint32_t data)
{
    uint32_t output;

    //              FIRST  -  -  -  -  -  -  -  -  -  -  -  LAST
    // Data Format: A0  A1  A2  A3  R/W  D0  D1  D2 ... D18  D19
    output = ((data << 5) | 0x10) + (addr & 0x0f);

    // start SPI transaction
    digitalWrite(spiClockPin, LOW);
    delayMicroseconds(1);
    digitalWrite(slaveSelectPin, LOW);
    delayMicroseconds(1);

    // clock out data LSB first
    for (uint8_t i = 25; i > 0; i--) {
        if (output & 0x01) {
              digitalWrite(spiDataPin, HIGH);  // output 1
        }
        else {
              digitalWrite(spiDataPin, LOW);   // output 0
        }
        delayMicroseconds(1);
        digitalWrite(spiClockPin, HIGH);   // data latched by 5823 here
        delayMicroseconds(1);
        digitalWrite(spiClockPin, LOW);    // clock ends low
        output >>= 1;                      // shift output data
        delayMicroseconds(1);
    }

    // terminate SPI transaction and set data low
    digitalWrite(slaveSelectPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(spiDataPin, LOW);
}
/*
 *  update the frequency registers on TX5823
 */
void set_5823_freq(uint16_t f)
{ // f is desired frequency in MHz
    uint32_t R = (uint32_t)f * 25;
    uint32_t N = R / 64;
    uint32_t A = R % 64;
    uint32_t h = N * 128 + A;
    uint32_t x = h % 65536;
    Serial.print("set.freq=");    Serial.print(f);
    Serial.print(" R=");    Serial.print(R);
    Serial.print(" N=");    Serial.print(N);
    Serial.print(" A=");    Serial.print(A);
    Serial.print(" h=");    Serial.print(h, HEX);
    Serial.print(" x=");    Serial.println(x, HEX);
    // add 0x00 04 00 00 to it
    uint32_t channelData = x + 0x00040000;

    //0x07: pre-driver & PA control (note: all variations with no effect, possibly due to separate second stage PA chip)
    //uint32_t a7 = 0b0100111110111101; // default from spec; pa5g_pw = 11
    //uint32_t a7 = 0b0100111100111101; // pa5g_pw = 10
    //uint32_t a7 = 0b0100111000111101; // pa5g_pw = 00
    //uint32_t a7 = 0b0100111110111101; // default from spec; pa5g_pw = 11, pa5g_bs =111
    //uint32_t a7 =  0b0100001010111000; // default from spec; pa5g_pw = 01, pa5g_bs =001
    //spi_write(0x07, a7);

    // Setting the R-Counter is not necessary every time but doesn't hurt
    spi_write(0x00, 0x0190);  // default value, provides 40kHz frequency resolution
    spi_write(0x01, channelData);   // write N and A counter-dividers (from channel table)


}

//----------------------------------------------------------------------------------
void updateFreqAndDisplay() {
	if (nextfreq != freq) {
		freq = nextfreq;
		set_5823_freq(freq);
		updateDisplay();
	}
}
//----------------------------------------------------------------------------------
void updateDisplay() {
	static uint16_t nlast = 0, flast = 0;
	//Serial.print(nextfreq);
	if (nextfreq != freq) {
		if (nextfreq != nlast)
			drawScreen.movingFreq(nextfreq);
			nlast = nextfreq;
			flast =  0;
	} else {
		if (freq != flast)
			drawScreen.screenSaver(freq, call_sign);
			flast = freq;
			nlast = 0;
	}
	//Serial.print(F("\n\n"));
	return;
}

// SETUP ----------------------------------------------------------------------------
void setup()
{

  Serial.begin(38400);
  Serial.println(F("\r\nRunning setup..."));
  pinMode(BUZ_PIN, OUTPUT);
  // Init Display
  if (drawScreen.begin(version) > 0)
  {
    // on Error flicker LED
    while (true)
    { // stay in ERROR for ever
      digitalWrite(BUZ_PIN, !digitalRead(BUZ_PIN));
      delay(100);
    }
  }
  drawScreen.splash(version, call_sign);
  TWBR = ((F_CPU / 400000) - 16) / 2; // change the I2C clock rate.

   encoder = new ClickEncoder(ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BTN_PIN, 4); // A, B, BTN, 4=stepsPerNotch fuer meine EC11
   encoder->setAccelerationEnabled(true);
   //encoder->setDoubleClickEnabled(false);
   ticker2.start(); //attach(1,cbtick1);
   delay(2000);

  // SPI pins for RX control
  pinMode (slaveSelectPin, OUTPUT);
  pinMode (spiDataPin, OUTPUT);
  pinMode (spiClockPin, OUTPUT);


  updateFreqAndDisplay();
  fanfare(7);
  ticker1.start(); // for updateDisplay
  Serial.println(F("-end of setup"));
}


// LOOP ----------------------------------------------------------------------------

void loop()
{
    ticker1.update();
    ticker2.update();

    // encoder:
    encoder_value = encoder->getValue();
    if (encoder_value != 0) {
      //Serial.print("Encoder encoder_value: ");
      Serial.println(encoder_value);
      buzz(BUZ_TICK);
      nextfreq += encoder_value;
      nextfreq = max( min(nextfreq, MHZ_RANGE_MAX), MHZ_RANGE_MIN);
    }

    // encoder-button :
    encoder_button = encoder->getButton();
    if (encoder_button != ClickEncoder::Open) {
      //Serial.print("Button: ");
      switch (encoder_button) {
      case  ClickEncoder::Pressed :
      case  ClickEncoder::Held :
        {
          Serial.print(F("pressed or held "));
          Serial.println(encoder_button);
            break;
        }
      case  ClickEncoder::Clicked :
        {
          Serial.println(F("Clicked "));
          buzz(BUZ_CLICK);
          // set to new freq is done here
          freq = nextfreq;
          // set the freq now
          set_5823_freq(freq);
          break;
        }
      case  ClickEncoder::DoubleClicked :
        {
          Serial.println(F("Double Clicked "));
          //Serial.println(encoder_button);
          fanfare(4); //buzz(BUZ_CLICK); delay(5); buzz(BUZ_CLICK);
          // do something?
          nextfreq = freq; // display back to normal
          // need not set the freq now
          // zzz
          break;
        }
      } // switch
    } // if
    //updateFreqAndDisplay();
}
