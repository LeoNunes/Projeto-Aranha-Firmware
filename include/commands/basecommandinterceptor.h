#pragma once

#include <Arduino.h>

#include <commands/commandinterceptor.h>

struct BaseCommandInterceptor : CommandInterceptor {
    bool intercept(String command) override;
};

inline BaseCommandInterceptor BASE_SERIAL_COMMAND_INTERCEPTOR = BaseCommandInterceptor();