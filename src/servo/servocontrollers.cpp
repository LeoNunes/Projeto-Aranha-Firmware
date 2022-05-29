#include <servo/servocontrollers.h>
#include <servo/servo.h>

void initializeServoControllers() {
    for (int i = 0; i < SERVO_COUNT; i++) {
        SERVO_CONTROLLERS[i] = new ServoController(ALL_SERVOS[i]);
    }
}

void servoControllersLoop() {
    for (int i = 0; i < SERVO_COUNT; i++) {
        SERVO_CONTROLLERS[i]->loop();
    }
}