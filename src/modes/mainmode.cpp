#include <Arduino.h>

#include <modes/mainmode.h>
#include <servo/servo.h>
#include <servo/servocontrollers.h>
#include <servo/instantmovement.h>
#include <servo/linearmovement.h>



void wakeUp() {
    for (int i = 0; i < 4; i++) {
        InstantMovement* m0_0 = new InstantMovement(0, 5000);
        SERVO_CONTROLLERS[3*i+0]->addMovementToQueue(m0_0);
        LinearMovement* m0_1 = new LinearMovement(0, 45, 1000);
        SERVO_CONTROLLERS[3*i+0]->addMovementToQueue(m0_1);

        InstantMovement* m1_0 = new InstantMovement(0, 6000);
        SERVO_CONTROLLERS[3*i+1]->addMovementToQueue(m1_0);
        LinearMovement* m1_1 = new LinearMovement(0, 70, 2000);
        SERVO_CONTROLLERS[3*i+1]->addMovementToQueue(m1_1);

        InstantMovement* m2_0 = new InstantMovement(0, 7000);
        SERVO_CONTROLLERS[3*i+2]->addMovementToQueue(m2_0);
        LinearMovement* m2_1 = new LinearMovement(0, 70, 1000);
        SERVO_CONTROLLERS[3*i+2]->addMovementToQueue(m2_1);
    }
}

void sleep() {
    for (int i = 0; i < SERVO_COUNT; i++) {
        InstantMovement* m = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[i]->addMovementToQueue(m);
    }
}

void MainMode::initiateMode() {
    Serial.println("--- Initiating Main Mode ---");

    #ifdef LEO_ENV

    // wakeUp();
    sleep();

    #endif
}

void MainMode::terminateMode() {
    Serial.println("--- Terminating Main Mode ---");
}

void MainMode::loop() {
    servoControllersLoop();
    // TODO: implement Main Mode
}
