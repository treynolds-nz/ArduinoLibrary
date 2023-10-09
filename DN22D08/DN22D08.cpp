#include "DN22D08.h"

const int DN22_InputPin_LUT[] = {0,2,3,4,5,6,7,9,11};  //one-based, indexable
const int DN22_SwitchKnPin_LUT[] = {12,10,8,A0};

#define RELAY1 15
#define RELAY2 16
#define RELAY3 17
#define RELAY4 18
#define RELAY5 19
#define RELAY6 20
#define RELAY7 21
#define RELAY8 22

#define RS485_RD A1

//how to handle the shiftRegs??????
static ShiftRegister74HC595<3> sr(dataPin, clockPin, latchPin);
//Map of the segment positions in the shift register, 
//							{G,F,E,D,C,B,A}
const int DN22_ABCDEFG_LUT[] = {19,14,9,11,15,20,12};
//Map of digit latch pins in the shift register, 
//				{digi0,digi1,digi2,digi3)
const int DN22_DigiN_LUT[] = {10,17,18,21};
//dot position in shift register
#define dotBit 13

void DN22D08::initialise()
{
   pinMode(OE_595, OUTPUT);
   digitalWrite(OE_595, LOW);// Enable 74HC595  
   
   pinMode(INPUT1, INPUT);
   pinMode(INPUT2, INPUT);
   pinMode(INPUT3, INPUT);
   pinMode(INPUT4, INPUT);
   pinMode(INPUT5, INPUT);
   pinMode(INPUT6, INPUT);
   pinMode(INPUT7, INPUT);
   pinMode(INPUT8, INPUT);     
   pinMode(K1pin, INPUT_PULLUP);
   pinMode(K2pin, INPUT_PULLUP);
   pinMode(K3pin, INPUT_PULLUP);
   pinMode(K4pin, INPUT_PULLUP); 
}

void DN22D08::digitalWrite(uint8_t relayNumber, uint8_t val)
{
  sr.set(relayNumber, val);
};

int DN22D08::digitalReadOpto(uint8_t optoInputNumber)
{
  return digitalRead(DN22_InputPin_LUT[optoInputNumber]);
};

int DN22D08::digitalReadSwitch(uint8_t Kn)
{
  return !digitalRead(DN22_SwitchKnPin_LUT[Kn]);	//active low
};

//The character do not latch in the display, they must be blinked if more than one character is displayed
//Only lit when segment pins are high and digit pin/s is low (common cathode)
void DN22D08::printCharToDigit(int DigitN, uint8_t ABCDEFGChar)
{
  sr.setNoUpdate(DN22_DigiN_LUT[0],HIGH);
  sr.setNoUpdate(DN22_DigiN_LUT[1],HIGH);
  sr.setNoUpdate(DN22_DigiN_LUT[2],HIGH);
  sr.setNoUpdate(DN22_DigiN_LUT[3],HIGH);
	switch(ABCDEFGChar)
	{
		case '.':
			//clear the segments
			sr.setNoUpdate(DN22_ABCDEFG_LUT[0],LOW);
			sr.setNoUpdate(DN22_ABCDEFG_LUT[1],LOW);
			sr.setNoUpdate(DN22_ABCDEFG_LUT[2],LOW);
			sr.setNoUpdate(DN22_ABCDEFG_LUT[3],LOW);
			sr.setNoUpdate(DN22_ABCDEFG_LUT[4],LOW);
			sr.setNoUpdate(DN22_ABCDEFG_LUT[5],LOW);
			sr.setNoUpdate(DN22_ABCDEFG_LUT[6],LOW);
			//set lower dot
			sr.setNoUpdate(DigitN,LOW);
			sr.set(dotBit,HIGH);
			break;
		default:			//Printable characters
			sr.setNoUpdate(dotBit,LOW);	//clear the decimal place
			//select digit
			sr.setNoUpdate(DN22_DigiN_LUT[DigitN],LOW);
			//load segments
			int bitN;
			for(bitN=0;bitN<7;bitN++)
			{
				sr.setNoUpdate((DN22_ABCDEFG_LUT[bitN]),(ABCDEFGChar & (1<<bitN)));
			}
			//load new value
			sr.updateRegisters();
			//deselect digit
			// sr.set(DN22_DigiN_LUT[DigitN],HIGH);
			break;
	}
	//Serial.print("DigitN:");Serial.println(DigitN);
	//Serial.print("ABCDEFGChar:");Serial.println(ABCDEFGChar);
}

void DN22D08::printString(uint8_t* asciiChar)
{
	int digit = 0;
	//loop first four characters or null character reached
	while((*asciiChar != 0) && digit < 4)
	{
		printCharToDigit(digit, seikooFont_LUT[*asciiChar]);
		asciiChar++;
		if(*asciiChar != '.') digit++;	//if the next character is a decimal place, print it at the same digit
	}
	//clear any remaining digits with spaces
	while(digit < 4)
	{
		printCharToDigit(digit, 0);
		digit++;
	}
	//clear last digit so it doesn't appear brighter than the rest
	printCharToDigit(3, 0);
}
