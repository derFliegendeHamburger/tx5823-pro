/*
 * Screens Class by Shea Ivey

The MIT License (MIT)

Copyright (c) 2015 Shea Ivey
**MODS George Chatzisavvidis

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

#ifndef display_h
#define display_h
 

//Each screen has the following
// public entry method
// private draw method
// public update method
// private update draw method

class screens
{
    private: // helper functions for screens.
        uint8_t last_rssi;
        uint8_t best_rssi;
        uint8_t copy_best_rssi, copy_bestRawRssiA, copy_bestRawRssiB;
        uint8_t best_channel;
        uint8_t bestRawRssiA, bestRawRssiB;
        uint8_t last_channel;
        uint16_t bestChannelName;
        uint16_t bestChannelFrequency;
        void reset();
        void drawTitleBox(const char *title, bool centerFlag = true);

    public:
        screens();
        char begin(const char *call_sign);
        void flip();
        void splash( const char *version, const char *call_sign);


        // SCREEN SAVER
        void movingFreq( uint16_t channelFrequency);
        void screenSaver( uint16_t channelFrequency, const char *call_sign);

};
#endif
