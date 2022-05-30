#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

// TODO: Refactor to allow skipping PINS (e.g. using pin 15 for servo 3);

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

const Servo S_FL_1 = SER0; // Front Left 1
const Servo S_FL_2 = SER1; // Front Left 2
const Servo S_FL_3 = SER2; // Front Left 3
const Servo S_FR_1 = SER3; // Front Right 1
const Servo S_FR_2 = SER4; // Front Right 2
const Servo S_FR_3 = SER5; // Front Right 3
const Servo S_BL_1 = SER6; // Back Left 1
const Servo S_BL_2 = SER7; // Back Left 2
const Servo S_BL_3 = SER8; // Back Left 3
const Servo S_BR_1 = SER9; // Back Right 1
const Servo S_BR_2 = SER10; // Back Right 2
const Servo S_BR_3 = SER11; // Back Right 3

const byte SERVO_COUNT = 12;
const Servo ALL_SERVOS[] { SER0, SER1, SER2, SER3, SER4, SER5, SER6, SER7, SER8, SER9, SER10, SER11 };

void initializePCA9685(uint8_t addr = 0x40);

void moveServo(Servo servo, int angle);