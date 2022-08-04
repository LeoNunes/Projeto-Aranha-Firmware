#include <Arduino.h>

#include <servo/legcontroller.h>
#include <servo/servocontroller.h>
#include <servo/instantmovement.h>
#include <servo/linearmovement.h>
#include <config.h>

LegController::LegController(
        ServoController* controller1,
        ServoController* controller2,
        ServoController* controller3) {
    this->servoControllers[0] = controller1;
    this->servoControllers[1] = controller2;
    this->servoControllers[2] = controller3;
}

void LegController::WakeSequence(byte finalAngle1, byte finalAngle2, byte finalAngle3) {
    InstantMovement* m0_0 = new InstantMovement(0, 1000);
    LinearMovement* m0_1 = new LinearMovement(0, finalAngle1, 1000);
    servoControllers[0]->addMovementToQueue(m0_0);
    servoControllers[0]->addMovementToQueue(m0_1);

    InstantMovement* m1_0 = new InstantMovement(0, 2000);
    LinearMovement* m1_1 = new LinearMovement(0, finalAngle2, 2000);
    servoControllers[1]->addMovementToQueue(m1_0);
    servoControllers[1]->addMovementToQueue(m1_1);

    InstantMovement* m2_0 = new InstantMovement(145, 2000);
    LinearMovement* m2_1 = new LinearMovement(145, finalAngle3, 1000);
    servoControllers[2]->addMovementToQueue(m2_0);
    servoControllers[2]->addMovementToQueue(m2_1);
}

void LegController::SleepSequence() {
    InstantMovement* movement0 = new InstantMovement(0, 1000);
    InstantMovement* movement1 = new InstantMovement(0, 1000);
    InstantMovement* movement2 = new InstantMovement(145, 1000);

    this->servoControllers[0]->addMovementToQueue(movement0);
    this->servoControllers[1]->addMovementToQueue(movement1);
    this->servoControllers[2]->addMovementToQueue(movement2);
}

void LegController::StoreSequence() {
    InstantMovement* movement0 = new InstantMovement(0, 1000);
    InstantMovement* movement1 = new InstantMovement(0, 1000);
    InstantMovement* movement2 = new InstantMovement(0, 1000);

    this->servoControllers[0]->addMovementToQueue(movement0);
    this->servoControllers[1]->addMovementToQueue(movement1);
    this->servoControllers[2]->addMovementToQueue(movement2);
}

void LegController::Rotate(byte fromAngle, byte toAngle, long durationInMillis) {
    LinearMovement* movement = new LinearMovement(fromAngle, toAngle, durationInMillis);
    this->servoControllers[0]->addMovementToQueue(movement);
}

void LegController::Step(byte fromAngle, byte toAngle, long durationInMillis) {
    
}

bool LegController::Moving() {
    for (byte i = 0; i < SERVOS_IN_THE_LEG; i++) {
        if (this->servoControllers[i]->queueSize() != 0) {
            return true;
        }
    }
    return false;
}

void LegController::loop() {
    for (byte i = 0; i < SERVOS_IN_THE_LEG; i++) {
        this->servoControllers[i]->loop();
    }
}