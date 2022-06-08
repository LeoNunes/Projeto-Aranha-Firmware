#pragma once

#include <Arduino.h>

#include <commands/commandprovider.h>

const byte BLUETOOTH_COMMAND_MAX_SIZE = 20;

struct BluetoothCommandProvider : CommandProvider {
    public:
        String getCommand() override;
    private:
        char bluetoothCommandValue[BLUETOOTH_COMMAND_MAX_SIZE];
        byte bluetoothCommandPosition = 0;

};

inline BluetoothCommandProvider BLUETOOTH_COMMAND_PROVIDER = BluetoothCommandProvider();
