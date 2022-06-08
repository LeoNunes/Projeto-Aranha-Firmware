#include <Arduino.h>

#include <bluetooth.h>
#include <commands/bluetoothcommandprovider.h>

String BluetoothCommandProvider::getCommand()
{
    if (SerialBT.available() > 0) {
        char nextChar = SerialBT.read();
        if (nextChar == '\n')
        {
            bluetoothCommandValue[bluetoothCommandPosition] = '\0';
            bluetoothCommandPosition = 0;
            String command(bluetoothCommandValue);
            return command;
        }
        else
        {
            bluetoothCommandValue[bluetoothCommandPosition] = nextChar;
            bluetoothCommandPosition++;
        }
    }
    return String("");
}