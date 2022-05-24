#pragma once

#include <modes/mode.h>

struct MainMode : Mode {
    public:
        void initiateMode() override;
        void terminateMode() override;
        void loop() override;
};