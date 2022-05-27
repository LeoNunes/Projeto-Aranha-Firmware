#pragma once

#include <Arduino.h>

#include <servo/servomovement.h>

struct LinearMovement : ServoMovement {
    public:
        LinearMovement(byte startAngle, byte finalAngle, long durationInMillis);
        void start() override;
        byte getAngle() override;
        bool getStarted() override;
        bool getCompleted() override;
    private:
        byte initialAngle;
        byte finalAngle;
        long durationInMillis;
        long startTimeInMillis;
        bool started;
        bool completed;
};
