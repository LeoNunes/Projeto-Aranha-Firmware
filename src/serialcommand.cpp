#include <Arduino.h>

#include "serialcommand.h"

const int COMMAND_MAX_SIZE = 20;


char serialCommandValue[COMMAND_MAX_SIZE];
byte serialCommandPosition = 0;

String readSerialCommand()
{
    if (Serial.available() > 0)
    {
        char nextChar = Serial.read();
        if (nextChar == '\n')
        {
            serialCommandValue[serialCommandPosition] = '\0';
            serialCommandPosition = 0;
            String command(serialCommandValue);
            Serial.print("Command received: ");
            Serial.println(command);
            return command;
        }
        else
        {
            serialCommandValue[serialCommandPosition] = nextChar;
            serialCommandPosition++;
        }
    }
    return String("");
}