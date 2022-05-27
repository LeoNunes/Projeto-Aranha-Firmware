#include <Arduino.h>

#include <servo/linearmovement.h>

LinearMovement::LinearMovement(byte initialAngle, byte finalAngle, long durationInMillis) {
    this->initialAngle = initialAngle;
    this->finalAngle = finalAngle;
    this->durationInMillis = durationInMillis;
    started = false;
    completed = false;
}

void LinearMovement::start() {
    startTimeInMillis = millis();
    started = true;
}

byte LinearMovement::getAngle() {
    if (millis() >= startTimeInMillis + durationInMillis) {
        completed = true;
        return finalAngle;
    }

    float ellapsedPercentage = (millis() - startTimeInMillis)/(float)durationInMillis;
    int deltaAngle = (int)finalAngle - (int)initialAngle; // Cast to int to allow negative numbers

    return (byte)(initialAngle + ellapsedPercentage*deltaAngle);
}

bool LinearMovement::getStarted() {
    return started;
}

bool LinearMovement::getCompleted() {
    return completed;
}
