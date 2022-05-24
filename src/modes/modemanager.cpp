#include <Arduino.h>

#include <modes/modemanager.h>

ModeManager::ModeManager() {
    initialized = false;
    currentMode = nullptr;
}

void ModeManager::executeModeLoop() {
    if (currentMode == nullptr) {
        Serial.println("No mode defined in ModeManager");
        delay(1000);
        return;
    }

    currentMode->loop();
}

void ModeManager::setMode(Mode& newMode) {
    if (initialized) {
        currentMode->terminateMode();
    }
    newMode.initiateMode();
    currentMode = &newMode;
    initialized = true;
}