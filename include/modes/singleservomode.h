#pragma once

#include <modes/mode.h>
#include <servo.h>
#include <serialcommands/commandinterceptor.h>

struct SingleServoMode : Mode, CommandInterceptor {
    public:
        void initiateMode() override;
        void terminateMode() override;
        void loop() override;
        bool intercept(String command) override;
    
    private:
        byte interceptorId;
        bool servoSelected;
        Servo servo;
};