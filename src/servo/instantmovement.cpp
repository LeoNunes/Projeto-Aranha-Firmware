#include <Arduino.h>

#include <servo/instantmovement.h>

InstantMovement::InstantMovement(byte angle, long delayInMillis) {
    this->angle = angle;
    this->delayInMillis = delayInMillis;
    started = false;
    completed = false;
}

void InstantMovement::start() {
    startTimeInMillis = millis();
    started = true;
}

byte InstantMovement::getAngle() {
    if (millis() >= startTimeInMillis + delayInMillis) {
        completed = true;
    }
    return angle;
}

bool InstantMovement::getStarted() {
    return started;
}

bool InstantMovement::getCompleted() {
    return completed;
}
