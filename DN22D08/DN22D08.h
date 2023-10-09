#ifndef DN22D08_H
#define DN22D08_H

/*******************************************************\
* DN22D08 is a 12V Relay adapter board for Arduino Nano
* that offers:
* - 8x DPST relays, driven from a 74HC595 8-bit shift register
* - 8X optically isolated input
* - 4 character 7 segment display, driven from 2 more 595's in series with the output driver
* - 4x onboard switches
* - 
\*******************************************************/

#include <Arduino.h>
#include <stdint.h>
#include <ShiftRegister74HC595.h>
#include <Siekoo.h>;

#define INPUT1 2
#define INPUT2 3
#define INPUT3 4
#define INPUT4 5
#define INPUT5 6
#define INPUT6 7
#define INPUT7 9
#define INPUT8 11

#define K1pin 12
#define K2pin 10
#define K3pin 8
#define K4pin A0

//uint8_t enum Kn {K1, K2, K3, K4};

//Pin connected to 595_OE of Digital Tube Module
 #define OE_595 A2
//Pin connected to latch of Digital Tube Module
 #define latchPin A3
//Pin connected to clock of Digital Tube Module
 #define clockPin A4
//Pin connected to data of Digital Tube Module
 #define dataPin A5

class DN22D08{
  public:
  void initialise();
  void digitalWrite(uint8_t relayNumber, uint8_t val);
  int digitalReadOpto(uint8_t optoInputNumber);
  int digitalReadSwitch(uint8_t Kn);
  void println(String val);
  void println(int val);
  void print(double val);
  void printCharToDigit(int DigitN, uint8_t ABCDEFGChar);
  //Print string of four characters max, plus four decimal places max
  //String is right justified,
  void printString(uint8_t* ABCDEFGChar);
};


#endif