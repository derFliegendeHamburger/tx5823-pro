//This '.ino' file is a stub to support building via the original
// Arduino IDE.  The real code is in the '.cpp' and '.h' files.
//
//The developer-preferred way of editing and building the project
//is via Eclipse and the "Eclipse C++ IDE for Arduino" plugin:
// https://marketplace.eclipse.org/content/eclipse-c-ide-arduino




// arduino 1.8.13 compile ok;

// eclipse.2021 with arduino: ProMini, 328P 5V 16MHz
// upload from eclipse.2021 via embedded  avrdude & red ftdi-adapter



// spi connects: CH1-3 -- D10-D12
// rotary encoder: A, B, BTN -- D5,D6,D8
// buzzer: D3

// v1.00 todo:
//		- 5V supply to board
//		- SPI connections to TX
//		- setFreq()
// v1.0c - setFreq() function ok -> software fully operational
// v1.0d - tried changes to video bandwidth but no good,
//		 - changes to gain & PA control w/o effect; reverted

