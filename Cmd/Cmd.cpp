#include "Cmd.h"
#include "Arduino.h"

// char cmd_buffer[Cmd_BufferSize][Cmd_PacketLengthMax+1]; //+1 for null terminator
String cmd_buffer[Cmd_BufferSize];
int cmd_buffer_WritePtr = 0;
int cmd_buffer_ReadPtr=0;

bool Cmd_LoadCommandToBuffer(String packet)
{
  cmd_buffer[cmd_buffer_WritePtr] = packet;
  cmd_buffer_WritePtr++;
  if(cmd_buffer_WritePtr >= Cmd_BufferSize) cmd_buffer_WritePtr = 0;
  return true;
}

bool Cmd_CheckForCommandAndCopy(String myName, String* packet)
{
  int readPtr;
  for(readPtr=0; readPtr<Cmd_BufferSize; readPtr++)
  {
    String pktName = cmd_buffer[readPtr].substring(0,cmd_buffer[readPtr].indexOf(String(Cmd_Delimiter)));
    if(pktName == myName)
    {
      *packet = cmd_buffer[readPtr].substring(cmd_buffer[readPtr].indexOf(String(Cmd_Delimiter))+1);
      cmd_buffer[readPtr] = String("");

      //Serial.println("Found");
      return true;
    }
  }
  return false;
}

static int pktIdx = 0;  //store for iterations

String Cmd_GetNextField(String packet, int index)
{
  if(index != -1) pktIdx = index;   //update if provided by caller
  String field = String("");  
  if(pktIdx < packet.length())      //check we're not off the end of the string
  {
    int fieldEnd = packet.indexOf(String(Cmd_Delimiter), pktIdx);
    if(fieldEnd==-1)  //not found
    {
      field = packet.substring(pktIdx); //so just read to end
      pktIdx = packet.length() +1;      //lock out for nect iteration (must be reset by caller)
    }
    else
    {
      field = packet.substring(pktIdx,fieldEnd);
      pktIdx = fieldEnd+1;  //record for next iteration, stepping over delimiter
    }
  }
  return field;
}
