#pragma once

#include <modes/mode.h>

struct ModeManager {
    public:
        ModeManager();
        void executeModeLoop();
        void setMode(Mode& newMode);

    private:
        Mode* currentMode;
};