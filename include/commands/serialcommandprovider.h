#pragma once

#include <Arduino.h>

#include <commands/commandprovider.h>

const byte SERIAL_COMMAND_MAX_SIZE = 20;

struct SerialCommandProvider : CommandProvider {
    public:
        String getCommand() override;
    private:
        char serialCommandValue[SERIAL_COMMAND_MAX_SIZE];
        byte serialCommandPosition = 0;

};

inline SerialCommandProvider SERIAL_COMMAND_PROVIDER = SerialCommandProvider();
