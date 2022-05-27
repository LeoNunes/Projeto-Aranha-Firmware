#include <Arduino.h>

#include <modes/modemanager.h>

ModeManager::ModeManager() {
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
    if (currentMode != nullptr) {
        currentMode->terminateMode();
    }
    newMode.initiateMode();
    currentMode = &newMode;
}