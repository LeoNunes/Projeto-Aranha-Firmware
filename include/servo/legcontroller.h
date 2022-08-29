#pragma once

#include <Arduino.h>

#include <servo/servocontroller.h>
#include <config.h>

struct LegController {
    public:
        LegController(
            ServoController* controller1,
            ServoController* controller2,
            ServoController* controller3
        );
        void WakeSequence(byte finalAngle1, byte finalAngle2, byte finalAngle3);
        void SleepSequence();
        void StoreSequence();
        void MoveTo(byte x, byte y);
        void StepTo(byte x, byte y);
        bool Moving();
        void loop();
    private:
        ServoController* servoControllers[SERVOS_IN_THE_LEG];
};
