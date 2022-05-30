#pragma once

#include <Arduino.h>

#include <modes/mode.h>
#include <servo/servo.h>
#include <serialcommands/serialcommandinterceptor.h>

struct CalibrationMode : Mode, SerialCommandInterceptor {
    public:
        void initiateMode() override;
        void terminateMode() override;
        void loop() override;
        bool intercept(String command) override;
    private:
        byte interceptorId;
        bool servoSelected;
        Servo selectedServo;
        bool angleSelected;
        byte selectedAngle;
        void resetAllCalibration();
        bool interceptForServoNotSelected(String command);
        bool interceptForServoSelectedAndAngleNotSelected(String command);
        bool interceptForServoAndAngleSelected(String command);
        void restartMode();
};
