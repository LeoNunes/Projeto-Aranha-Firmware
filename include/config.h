#pragma once

#include <Arduino.h>

const byte SERVO_COUNT = 12;
const byte LEGS_COUNT = 4;
const byte SERVOS_IN_THE_LEG = 3;

// Servo number for each position
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

// Map the servo number to its connector number
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

// Servo controllers uses a queue to control movements.
// This parameter defines its maximum size.
const byte MAX_MOVEMENT_QUEUE_SIZE = 5;

// Dimensions of the spider
const float LEG_SEGMENT_1_SIZE_IN_MM = 27.5;
const float LEG_SEGMENT_2_SIZE_IN_MM = 55;
const float LEG_SEGMENT_3_SIZE_IN_MM = 77.5;

// How far the body will be from the ground
const float DEFAULT_OPERATIONAL_BODY_HIGHT_IN_MM = 10;
