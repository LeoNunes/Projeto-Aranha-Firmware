#pragma once

#include <Arduino.h>

#include <commands/commandprovider.h>
#include <commands/commandinterceptor.h>

const byte MAX_COMMAND_PROVIDERS = 2;
const byte MAX_COMMAND_INTERCEPTORS = 10;

struct CommandManager {
    public:
        byte addCommandProvider(CommandProvider&);
        byte addCommandInterceptor(CommandInterceptor&);
        void removeCommandInterceptor(byte interceptorId);
        void run();
    private:
        byte nextProviderId = 0;
        CommandProvider* providers[MAX_COMMAND_PROVIDERS];
        byte nextInterceptorId = 0;
        CommandInterceptor* interceptors[MAX_COMMAND_INTERCEPTORS];
};

inline CommandManager COMMAND_MANAGER = CommandManager();
