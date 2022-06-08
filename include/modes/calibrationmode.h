#pragma once

#include <Arduino.h>

#include <modes/mode.h>
#include <servo/servo.h>
#include <commands/commandinterceptor.h>

struct CalibrationMode : Mode, CommandInterceptor {
    public:
        void initiateMode() override;
        void terminateMode() override;
        void loop() override;
        bool intercept(String command) override;
    private:
        byte interceptorId;
        bool servoSelected;
        Servo servo;
        bool zeroAngleSelected;
        byte zeroAngle;
        bool ninetyAngleSelected;
        byte ninetyAngle;
        void restartMode();
        bool interceptForGettingServo(String command);
        bool interceptForGettingZeroAngle(String command);
        bool interceptForGettingNinetyAngle(String command);
        bool interceptForCommit(String command);
        void readAllCalibration();
        void resetAllCalibration();
};
