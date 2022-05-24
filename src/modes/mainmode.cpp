#include <Arduino.h>

#include <modes/mainmode.h>

void MainMode::initiateMode() {
    Serial.println("--- Initiating Main Mode ---");
}

void MainMode::terminateMode() {
    Serial.println("--- Terminating Main Mode ---");
}

void MainMode::loop() {
    // TODO: implement Main Mode
}