#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <serialcommands/serialcommandmanager.h>
#include <serialcommands/baseserialcommandinterceptor.h>
#include <modes/modes.h>
#include <servo/servocontrollers.h>

void setup() {
    Serial.begin(115200);

    initializeServoControllers();

    initializePCA9685();
    delay(50);
    
    MODE_MANAGER.setMode(MAIN_MODE);
    COMMAND_MANAGER.addCommandInterceptor(BASE_SERIAL_COMMAND_INTERCEPTOR);
}

void loop() {
    MODE_MANAGER.executeModeLoop();
    COMMAND_MANAGER.run();
}
