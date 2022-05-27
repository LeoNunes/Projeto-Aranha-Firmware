#pragma once

#include <Arduino.h>

#include <servo/servomovement.h>

/* Instantaneous movement. Can have a delay after the movement */
struct InstantMovement : ServoMovement {
    public:
        InstantMovement(byte angle, long delayInMillis = 0);
        void start() override;
        byte getAngle() override;
        bool getStarted() override;
        bool getCompleted() override;
    private:
        byte angle;
        long delayInMillis;
        long startTimeInMillis;
        bool started;
        bool completed;
};