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

void LegController::MoveTo(float x, float y, float z, long durationInMillis) {
    float angle0, angle1, angle2;

    getAnglesForCartesian(x, y, z, angle0, angle1, angle2);

    LinearMovement* m0 = new LinearMovement(lastAngle0, angle0, durationInMillis);
    LinearMovement* m1 = new LinearMovement(lastAngle1, angle1, durationInMillis);
    LinearMovement* m2 = new LinearMovement(lastAngle2, angle2, durationInMillis);
    servoControllers[0]->addMovementToQueue(m0);
    servoControllers[1]->addMovementToQueue(m1);
    servoControllers[2]->addMovementToQueue(m2);
    lastAngle0 = angle0;
    lastAngle1 = angle1;
    lastAngle2 = angle2;
    lastX = x;
    lastY = y;
    lastZ = z;
}

void LegController::StepTo(float x, float y, float z, long durationInMillis) {
    float halfDurationInMillis = durationInMillis / 2;
    float halfX = (x - lastX) / 2 + lastX;
    float halfY = (y - lastY) / 2 + lastY;
    float halfZ = (z - lastZ) / 2 + lastZ + STEP_Z_HIGHT_IN_MM;

    MoveTo(halfX, halfY, halfZ, halfDurationInMillis);

    MoveTo(x, y, z, halfDurationInMillis);
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

void LegController::getAnglesForCartesian(volatile float x, volatile float y, volatile float z, volatile float &angle0, volatile float &angle1, volatile float &angle2) {
    float v, w;
    w = (x >= 0 ? 1 : -1) * (sqrt(pow(x, 2) + pow(y, 2)));
    v = w - LEG_SEGMENT_1_SIZE_IN_MM;
    angle1 = atan2(z, v) + acos((pow(LEG_SEGMENT_2_SIZE_IN_MM, 2) - pow(LEG_SEGMENT_3_SIZE_IN_MM, 2) + pow(v, 2) + pow(z, 2)) / 2 / LEG_SEGMENT_2_SIZE_IN_MM / sqrt(pow(v, 2) + pow(z, 2)));
    angle2 = acos((pow(LEG_SEGMENT_2_SIZE_IN_MM, 2) + pow(LEG_SEGMENT_3_SIZE_IN_MM, 2) - pow(v, 2) - pow(z, 2)) / 2 / LEG_SEGMENT_2_SIZE_IN_MM / LEG_SEGMENT_3_SIZE_IN_MM);
    //calculate x-y-z degree
    angle0 = (w >= 0) ? atan2(y, x) : atan2(-y, -x);
    //trans degree pi->180
    angle1 = angle1 / PI * 180;
    angle2 = angle2 / PI * 180;
    angle0 = angle0 / PI * 180;

    // Corrections for the way we are calibrating the angles
    angle2 = 180 - angle2;
    angle1 = 90 - angle1;

    if (angle0 < 0 || angle0 > 180) {
        while (1) {
            Serial.println("ERRO");
            delay(1000);
            // TODO Add error message
        }
    }
    if (angle1 < 0 || angle1 > 180) {
        while (1) {
            Serial.println("ERRO");
            delay(1000);
            // TODO Add error message
        }
    }
    if (angle2 < 0 || angle2 > 180) {
        while (1) {
            Serial.println("ERRO");
            delay(1000);
            // TODO Add error message
        }
    }
}