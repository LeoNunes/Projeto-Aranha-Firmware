#pragma once

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#define SER0 0 // Servo Motor 0 on connector 0
#define SER1 1 // Servo Motor 1 on connector 1
#define SER2 2 // Servo Motor 2 on connector 2
#define SER3 3 // Servo Motor 3 on connector 3
#define SER4 4 // Servo Motor 4 on connector 4
#define SER5 5 // Servo Motor 5 on connector 5
#define SER6 6 // Servo Motor 6 on connector 6
#define SER7 7 // Servo Motor 7 on connector 7
#define SER8 8 // Servo Motor 8 on connector 8
#define SER9 9 // Servo Motor 9 on connector 9
#define SER10 10 // Servo Motor 10 on connector 10
#define SER11 11 // Servo Motor 11 on connector 11
#define SER12 12 // Servo Motor 12 on connector 12

void initializePCA9685(uint8_t addr = 0x40);

void moveServo(byte motorAddress, int angle);