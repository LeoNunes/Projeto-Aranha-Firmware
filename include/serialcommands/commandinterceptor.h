#pragma once

#include <Arduino.h>

struct CommandInterceptor {
    virtual bool intercept(String command) = 0;
};