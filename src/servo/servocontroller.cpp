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

void ServoController::updateCalibration(bool reversed, byte zeroAngle) {
    this->reversed = reversed;
    this->zeroAngle = zeroAngle;
    EEPROM.writeBool(getReversedEEPROMAddress(), reversed);
    EEPROM.writeByte(getZeroAngleEEPROMAddress(), zeroAngle);
}

std::tuple<bool, byte> ServoController::getCalibration() {
    return std::make_tuple(reversed, zeroAngle);
}

void ServoController::resetCalibration() {
    byte EEPROM_address = servo * 2;
    EEPROM.writeBool(getReversedEEPROMAddress(), false);
    EEPROM.writeByte(getZeroAngleEEPROMAddress(), 0);
}

void ServoController::updateCalibrationFromStoredData() {
    reversed = EEPROM.readBool(getReversedEEPROMAddress());
    zeroAngle = EEPROM.readByte(getZeroAngleEEPROMAddress());
}

byte ServoController::getCorrectedAngleFor(byte angle) {
    int correctedAngle;
    if (reversed) {
        correctedAngle = zeroAngle - angle;
    } else {
        correctedAngle = zeroAngle + angle;
    }
    return correctedAngle;
}

byte ServoController::getReversedEEPROMAddress() {
    return servo * 2;
}
byte ServoController::getZeroAngleEEPROMAddress() {
    return getReversedEEPROMAddress() + 1;
}
