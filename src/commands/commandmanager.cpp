#include <Arduino.h>

#include <commands/commandmanager.h>
#include <commands/commandprovider.h>
#include <commands/commandinterceptor.h>

byte CommandManager::addCommandProvider(CommandProvider& provider) {
    if (nextProviderId >= MAX_COMMAND_PROVIDERS) {
        while (true) {
            Serial.println("Command Manager has no space for new providers");
            delay(1000);
        }
    }

    providers[nextProviderId] = &provider;

    byte providerId = nextProviderId;
    nextProviderId++;
    return providerId;
}

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
    for (int i = interceptorId; i < nextInterceptorId; i++) {
        interceptors[i] = interceptors[i+1];
    }
    nextInterceptorId--;
}

void CommandManager::run() {
    for (byte providerIndex = 0; providerIndex < nextProviderId; providerIndex++) {
        String command = providers[providerIndex]->getCommand();
    
        bool intercepted = false;
        if (command != "") {
            command.toUpperCase();
            for (byte interceptorIndex = 0; interceptorIndex < nextInterceptorId; interceptorIndex++) {
                if (interceptors[interceptorIndex]->intercept(command)) {
                    intercepted = true;
                    break;
                }
            }
            if (!intercepted) {
                Serial.print("Command unkwown: ");
                Serial.println(command);
            }
        }
    }
}
