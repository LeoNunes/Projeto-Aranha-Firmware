#pragma once

#include <modes/mode.h>
#include <commands/commandinterceptor.h>

struct BehaviorMode : Mode, CommandInterceptor {
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