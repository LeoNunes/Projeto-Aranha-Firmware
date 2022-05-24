#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

enum Servo : byte {
    SER0 = 0, // Servo Motor 0 on connector 0
    SER1 = 1, // Servo Motor 1 on connector 1
    SER2 = 2, // Servo Motor 2 on connector 2
    SER3 = 3, // Servo Motor 3 on connector 3
    SER4 = 4, // Servo Motor 4 on connector 4
    SER5 = 5, // Servo Motor 5 on connector 5
    SER6 = 6, // Servo Motor 6 on connector 6
    SER7 = 7, // Servo Motor 7 on connector 7
    SER8 = 8, // Servo Motor 8 on connector 8
    SER9 = 9, // Servo Motor 9 on connector 9
    SER10 = 10, // Servo Motor 10 on connector 10
    SER11 = 11, // Servo Motor 11 on connector 11
};

const byte SERVO_COUNT = 12;
const Servo ALL_SERVOS[] { SER0, SER1, SER2, SER3, SER4, SER5, SER6, SER7, SER8, SER9, SER10, SER11 };

void initializePCA9685(uint8_t addr = 0x40);

void moveServo(Servo servo, int angle);