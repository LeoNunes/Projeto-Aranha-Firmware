#include <Arduino.h>

#include <commands/serialcommandprovider.h>

String SerialCommandProvider::getCommand()
{
    if (Serial.available() > 0) {
        char nextChar = Serial.read();
        if (nextChar == '\n')
        {
            serialCommandValue[serialCommandPosition] = '\0';
            serialCommandPosition = 0;
            String command(serialCommandValue);
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