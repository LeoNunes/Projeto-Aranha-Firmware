#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <EEPROM.h>

#include <bluetooth.h>
#include <commands/commandmanager.h>
#include <commands/basecommandinterceptor.h>
#include <commands/serialcommandprovider.h>
#include <commands/bluetoothcommandprovider.h>
#include <modes/modes.h>
#include <servo/servocontrollers.h>
#include <config.h>

void setup() {
    Serial.begin(115200);
    SerialBT.begin("Spider");

    // Numbers of byte to be persisted in EEPROM:
    // - Two bytes for each servo holding the calibration data (0 and 90 degree angle values)
    byte EEPROM_CalibrationSize = SERVO_COUNT * 2;
    EEPROM.begin(EEPROM_CalibrationSize);

    initializeServoControllers();

    initializePCA9685();
    delay(50);
    
    MODE_MANAGER.setMode(MAIN_MODE);
    COMMAND_MANAGER.addCommandProvider(SERIAL_COMMAND_PROVIDER);
    COMMAND_MANAGER.addCommandProvider(BLUETOOTH_COMMAND_PROVIDER);
    COMMAND_MANAGER.addCommandInterceptor(BASE_SERIAL_COMMAND_INTERCEPTOR);
}

void loop() {
    MODE_MANAGER.executeModeLoop();
    COMMAND_MANAGER.run();
}
