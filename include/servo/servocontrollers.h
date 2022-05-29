#pragma once

#include <servo/servo.h>
#include <servo/servocontroller.h>

inline ServoController* SERVO_CONTROLLERS[SERVO_COUNT];

void initializeServoControllers();
void servoControllersLoop();
