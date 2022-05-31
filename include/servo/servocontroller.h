#pragma once

#include <Arduino.h>
#include <cppQueue.h>

#include <servo/servo.h>
#include <servo/servomovement.h>

const byte MAX_MOVEMENT_QUEUE_SIZE = 5;

struct ServoController {
    public:
        ServoController(Servo servo);
        ~ServoController();
        void addMovementToQueue(ServoMovement* movement);
        void loop();
        void updateCalibration(byte zeroAngle, byte ninetyAngle);
        std::tuple<byte, byte> getCalibration();
        void resetCalibration();
    private:
        Servo servo;
        cppQueue* movementQueue;
        byte zeroAngle;
        byte ninetyAngle;
        byte getCorrectedAngleFor(byte angle);
        void updateCalibrationFromStoredData();
        byte getZeroAngleEEPROMAddress();
        byte getNinetyAngleEEPROMAddress();
};