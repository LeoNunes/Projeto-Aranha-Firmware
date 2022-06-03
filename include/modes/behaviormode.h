#pragma once

#include <modes/mode.h>
#include <serialcommands/serialcommandinterceptor.h>

struct BehaviorMode : Mode, SerialCommandInterceptor {
    public:
        void initiateMode() override;
        void terminateMode() override;
        void loop() override;
        bool intercept(String command) override;
    private:
        byte interceptorId;
        void executeWake();
        void executeSleep();
        void executeStore();
};