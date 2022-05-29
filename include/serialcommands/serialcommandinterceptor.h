#pragma once

#include <Arduino.h>

struct SerialCommandInterceptor {
    virtual bool intercept(String command) = 0;
};