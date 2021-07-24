# tx5823spiTransmitter / tx5823-pro
The tx5823spiTransmitter is derived from tx5823-pro sheaivey's transmitter project. 

## Features
Frequency selection is done via rotary encoder and allows for tuning of frequency with a stepsize of 1 MHz, in the range of [5505 ; 5995] MHz. Frequency is shown on OLED in large font (not much else to display anyways)

## Hardware
In my case, the transmitter module with the RTC6705 was taken from an TS5823 which is nice because the module comes already converted to SPI mode.
Display is SSD1306 128x64 OLED (because it was available).
Connections as usual or as outlined the the main cpp file.

## Usage:
Use rotary encoder to select desired frequency,
then use single click to set the transmitter to this frequency, or
use double click to abort frequency change.

![v10d](https://user-images.githubusercontent.com/16653051/126883214-411c316f-831a-4191-81ad-c4ae75440815.jpg)

## License & Recognition
#### Recognition
* Original project idea of IR controlled video transmitter by Shea Ivey
* Schematics by Shea Ivey
* Source by Shea Ivey

#### License
The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
