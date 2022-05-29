#pragma once

#include <Arduino.h>

#include <serialcommands/serialcommandinterceptor.h>

struct BaseSerialCommandInterceptor : SerialCommandInterceptor {
    bool intercept(String command) override;
};

inline BaseSerialCommandInterceptor BASE_SERIAL_COMMAND_INTERCEPTOR = BaseSerialCommandInterceptor();