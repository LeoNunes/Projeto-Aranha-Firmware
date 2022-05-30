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
        void updateCalibration(bool reversed, byte zeroAngle);
        std::tuple<bool, byte> getCalibration();
        void resetCalibration();
    private:
        Servo servo;
        cppQueue* movementQueue;
        bool reversed;
        byte zeroAngle;
        byte getCorrectedAngleFor(byte angle);
        void updateCalibrationFromStoredData();
        byte getReversedEEPROMAddress();
        byte getZeroAngleEEPROMAddress();
};