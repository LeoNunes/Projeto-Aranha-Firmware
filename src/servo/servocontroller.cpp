#include <Arduino.h>
#include <cppQueue.h>
#include <EEPROM.h>

#include <servo/servocontroller.h>
#include <servo/servomovement.h>
#include <servo/servo.h>

ServoController::ServoController(Servo servo) {
    this->servo = servo;
    movementQueue = new cppQueue(sizeof(ServoMovement*), MAX_MOVEMENT_QUEUE_SIZE, FIFO);
    updateCalibrationFromStoredData();
}

ServoController::~ServoController() {
    while (!movementQueue->isEmpty()) {
        ServoMovement* movement;
        movementQueue->pop(&movement);
        delete movement;
    }
    delete movementQueue;
}

void ServoController::addMovementToQueue(ServoMovement* movement) {
    if (movementQueue->isFull()) {
        while (true) {
            Serial.print("Movement queue for Servo ");
            Serial.print(servo);
            Serial.print("is full");
            delay(1000);
        }
    }
    movementQueue->push(&movement);
}

void ServoController::loop() {
    ServoMovement* movement;
    if (movementQueue->peek(&movement)) {
        if (!movement->getStarted()) {
            movement->start();
        }

        moveServo(servo, getCorrectedAngleFor(movement->getAngle()));

        if (movement->getCompleted()) {
            movementQueue->pop(&movement);
            delete movement;
        }
    }
}

void ServoController::updateCalibration(byte zeroAngle, byte ninetyAngle) {
    this->zeroAngle = zeroAngle;
    this->ninetyAngle = ninetyAngle;
    EEPROM.writeByte(getZeroAngleEEPROMAddress(), zeroAngle);
    EEPROM.writeByte(getNinetyAngleEEPROMAddress(), ninetyAngle);
    EEPROM.commit();
}

std::tuple<byte, byte> ServoController::getCalibration() {
    return std::make_tuple(zeroAngle, ninetyAngle);
}

void ServoController::resetCalibration() {
    updateCalibration(0, 90);
}

void ServoController::updateCalibrationFromStoredData() {
    zeroAngle = EEPROM.readByte(getZeroAngleEEPROMAddress());
    ninetyAngle = EEPROM.readByte(getNinetyAngleEEPROMAddress());
}

byte ServoController::getCorrectedAngleFor(byte angle) {
    float coefficient = ((int)ninetyAngle - (int)zeroAngle)/90.0F;
    return (byte)((int)zeroAngle + coefficient*(float)angle);
}

byte ServoController::getZeroAngleEEPROMAddress() {
    return servo * 2;
}
byte ServoController::getNinetyAngleEEPROMAddress() {
    return getZeroAngleEEPROMAddress() + 1;
}

byte ServoController::queueSize() {
    return movementQueue->getCount();
}
