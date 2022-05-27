#pragma once

#include <Arduino.h>

#include <serialcommands/commandinterceptor.h>

struct BaseSerialCommandInterceptor : CommandInterceptor {
    bool intercept(String command) override;
};

inline BaseSerialCommandInterceptor BASE_SERIAL_COMMAND_INTERCEPTOR = BaseSerialCommandInterceptor();