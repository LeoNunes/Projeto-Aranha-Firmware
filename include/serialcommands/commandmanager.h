#pragma once

#include <serialcommands/commandinterceptor.h>

const byte MAX_COMMAND_INTERCEPTORS = 10;

struct CommandManager {
    public:
        byte addCommandInterceptor(CommandInterceptor&);
        void removeCommandInterceptor(byte interceptorId);
        void run();
    private:
        byte nextInterceptorId = 0;
        CommandInterceptor* interceptors[MAX_COMMAND_INTERCEPTORS];
};

inline CommandManager COMMAND_MANAGER = CommandManager();