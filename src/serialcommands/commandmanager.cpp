#include <Arduino.h>

#include <serialcommands/commandmanager.h>
#include <serialcommands/commandinterceptor.h>
#include <serialcommands/serialcommand.h>

byte CommandManager::addCommandInterceptor(CommandInterceptor& interceptor) {
    if (nextInterceptorId >= MAX_COMMAND_INTERCEPTORS) {
        while (true) {
            Serial.println("Command Manager has no space for new interceptors");
            delay(1000);
        }
    }

    interceptors[nextInterceptorId] = &interceptor;

    byte interceptorId = nextInterceptorId;
    nextInterceptorId++;
    return interceptorId;
}

void CommandManager::removeCommandInterceptor(byte interceptorId) {
    Serial.println("Chamado remove");
    for (int i = interceptorId; i < nextInterceptorId; i++) {
        interceptors[i] = interceptors[i+1];
    }
    nextInterceptorId--;
}

void CommandManager::run() {
    String command = readSerialCommand();
    if (command != "") {
        command.toUpperCase();
        for (int i = 0; i < nextInterceptorId; i ++) {
            if (interceptors[i]->intercept(command)) {
                break;
            }
        }
    }
}
