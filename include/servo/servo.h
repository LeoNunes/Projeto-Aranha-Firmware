#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

const byte SERVO_COUNT = 12;

enum Servo : byte {
    SER0 = 0, // Servo Motor 0
    SER1 = 1, // Servo Motor 1
    SER2 = 2, // Servo Motor 2
    SER3 = 3, // Servo Motor 3
    SER4 = 4, // Servo Motor 4
    SER5 = 5, // Servo Motor 5
    SER6 = 6, // Servo Motor 6
    SER7 = 7, // Servo Motor 7
    SER8 = 8, // Servo Motor 8
    SER9 = 9, // Servo Motor 9
    SER10 = 10, // Servo Motor 10
    SER11 = 11, // Servo Motor 11
};

const Servo ALL_SERVOS[] { SER0, SER1, SER2, SER3, SER4, SER5, SER6, SER7, SER8, SER9, SER10, SER11 };

const byte SER_FL_1 = 0; // Servo number for Front Left 1
const byte SER_FL_2 = 1; // Servo number for Front Left 2
const byte SER_FL_3 = 2; // Servo number for Front Left 3
const byte SER_FR_1 = 3; // Servo number for Front Right 1
const byte SER_FR_2 = 4; // Servo number for Front Right 2
const byte SER_FR_3 = 5; // Servo number for Front Right 3
const byte SER_BL_1 = 6; // Servo number for Back Left 1
const byte SER_BL_2 = 7; // Servo number for Back Left 2
const byte SER_BL_3 = 8; // Servo number for Back Left 3
const byte SER_BR_1 = 9; // Servo number for Back Right 1
const byte SER_BR_2 = 10; // Servo number for Back Right 2
const byte SER_BR_3 = 11; // Servo number for Back Right 3

const byte SERVOS_PINS[SERVO_COUNT] = {
    0, // Servo Motor 0 on connector 0
    1, // Servo Motor 1 on connector 1
    2, // Servo Motor 2 on connector 2
    3, // Servo Motor 3 on connector 3
    4, // Servo Motor 4 on connector 4
    5, // Servo Motor 5 on connector 5
    6, // Servo Motor 6 on connector 6
    7, // Servo Motor 7 on connector 7
    8, // Servo Motor 8 on connector 8
    9, // Servo Motor 9 on connector 9
    10, // Servo Motor 10 on connector 10
    11, // Servo Motor 11 on connector 11
};

void initializePCA9685(uint8_t addr = 0x40);

void moveServo(Servo servo, int angle);