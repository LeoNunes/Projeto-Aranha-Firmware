#pragma once

#include <Arduino.h>

struct ServoMovement {
    public:
        virtual void start() = 0;
        virtual byte getAngle() = 0;
        virtual bool getStarted() = 0;
        virtual bool getCompleted() = 0;
};
