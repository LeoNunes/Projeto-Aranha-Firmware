#pragma once

#include <Arduino.h>

#include <modes/mode.h>
#include <commands/commandinterceptor.h>
#include <servo/servocontroller.h>

struct CalibratedSingleServoMode : Mode, CommandInterceptor {
    public:
        void initiateMode() override;
        void terminateMode() override;
        void loop() override;
        bool intercept(String command) override;
    private:
        byte interceptorId;
        bool servoSelected = false;
        ServoController* servoController;
};