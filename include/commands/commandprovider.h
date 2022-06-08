#pragma once

#include <Arduino.h>

struct CommandProvider {
    public:
        virtual String getCommand() = 0;
};