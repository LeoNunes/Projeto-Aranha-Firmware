#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <serialcommand.h>
#include <servo.h>


void setup()
{
    Serial.begin(115200);

    initializePCA9685();
}

void loop()
{
    String command = readSerialCommand();
    if (command != "") {
        int angle = command.toInt();

        moveServo(SER0, angle);
    }
}
