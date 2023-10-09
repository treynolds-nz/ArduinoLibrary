#ifndef Cmd_h
#define Cmd_h

#include "Arduino.h"  //for String

#define Cmd_Delimiter ":"
#define Cmd_BufferSize 10

bool Cmd_LoadCommandToBuffer(String packet);
bool Cmd_CheckForCommandAndCopy(String myName, String* packet);
String Cmd_GetNextField(String packet, int index = -1);

#endif