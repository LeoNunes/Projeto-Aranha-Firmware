#pragma once

#include <Arduino.h>

#include <serialcommands/serialcommandinterceptor.h>

const byte MAX_COMMAND_INTERCEPTORS = 10;

struct SerialCommandManager {
    public:
        byte addCommandInterceptor(SerialCommandInterceptor&);
        void removeCommandInterceptor(byte interceptorId);
        void run();
    private:
        byte nextInterceptorId = 0;
        SerialCommandInterceptor* interceptors[MAX_COMMAND_INTERCEPTORS];
};

inline SerialCommandManager COMMAND_MANAGER = SerialCommandManager();