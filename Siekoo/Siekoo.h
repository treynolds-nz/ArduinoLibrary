#ifndef Siekoo_h
#define Siekoo_h

//LUT matching ASCII character values to Siekoo ABCDEFG 7-segment characters
//ABCDEFG format assumes display is A at top, then clockwise to F, with G in middle.
//A is msb, G is lsb
//Underscore (8) is the default value for unprintable characters
//Decimal place '.' uses its own ASCII value as a special character to be handled differently
const uint8_t seikooFont_LUT[] = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
						0,	//space
						8,8,8,8,8,8,
						32,
						8,8,8,8,8,
						1,	//apostraphe
						'.',//decimal place
						8,
						126,48,109,121,51,91,95,112,127,123,	//numerals
						8,8,8,8,8,8,8,
						125,31,13,61,79,71,94,23,68,88,87,14,85,21,29,103,115,5,90,15,28,42,43,20,59,108,	//Upper case
						8,8,8,8,
						8,	//underscore
						8,
						125,31,13,61,79,71,94,23,68,88,87,14,85,21,29,103,115,5,90,15,28,42,43,20,59,108,	//Lower case - same as upper
						8,8,8,8,8};
								
#endif