#include <Arduino.h>

#include <modes/mainmode.h>
#include <servo/servo.h>
#include <servo/servocontroller.h>
#include <servo/instantmovement.h>
#include <servo/linearmovement.h>


ServoController MM_ServoController = ServoController(S_FR_1);

void MainMode::initiateMode() {
    Serial.println("--- Initiating Main Mode ---");

    #ifdef LEO_ENV

    InstantMovement* m1 = new InstantMovement(40, 5000);
    LinearMovement* m2 = new LinearMovement(40, 115, 2000);
    InstantMovement* m3 = new InstantMovement(115, 1000);
    LinearMovement* m4 = new LinearMovement(115, 40, 1000);
    
    MM_ServoController.addMovementToQueue(m1);
    MM_ServoController.addMovementToQueue(m2);
    MM_ServoController.addMovementToQueue(m3);
    MM_ServoController.addMovementToQueue(m4);

    // delay(10000);
    // moveServo(S_FL_1, 65);
    // moveServo(S_FR_1, 85);
    // moveServo(S_BL_1, 75);
    // moveServo(S_BR_1, 50);
    // delay(1000);
    // moveServo(S_FL_2, 32);
    // moveServo(S_FR_2, 130);
    // moveServo(S_BL_2, 110);
    // moveServo(S_BR_2, 20);
    // delay(1000);
    // moveServo(S_FL_3, 80);
    // moveServo(S_FR_3, 100);
    // moveServo(S_BL_3, 100);
    // moveServo(S_BR_3, 70);
    // delay(1000);

    #endif
}

void MainMode::terminateMode() {
    Serial.println("--- Terminating Main Mode ---");
}

void MainMode::loop() {
    MM_ServoController.loop();
    // TODO: implement Main Mode
}