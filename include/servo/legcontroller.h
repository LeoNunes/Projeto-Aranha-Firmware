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
        void MoveTo(float x, float y, float z, long durationInMillis = 1000);
        void StepTo(float x, float y, float z, long durationInMillis = 1000);
        bool Moving();
        void loop();
    private:
        ServoController* servoControllers[SERVOS_IN_THE_LEG];
        float lastX;
        float lastY;
        float lastZ;
        byte lastAngle0 = 0;
        byte lastAngle1 = 0;
        byte lastAngle2 = 0;
        void getAnglesForCartesian(volatile float x, volatile float y, volatile float z, volatile float &angle0, volatile float &angle1, volatile float &angle2);
};
