#pragma once

#include <Arduino.h>
#include <cppQueue.h>

#include <servo/servo.h>
#include <servo/servomovement.h>

struct ServoController {
    public:
        ServoController(Servo servo);
        ~ServoController();
        void addMovementToQueue(ServoMovement* movement);
        void loop();
        void updateCalibration(byte zeroAngle, byte ninetyAngle);
        std::tuple<byte, byte> getCalibration();
        void resetCalibration();
        byte queueSize();
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