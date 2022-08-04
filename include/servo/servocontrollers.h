#pragma once

#include <config.h>
#include <servo/servocontroller.h>

inline ServoController* SERVO_CONTROLLERS[SERVO_COUNT];

void initializeServoControllers();

// TODO: Remove this
void servoControllersLoop();
