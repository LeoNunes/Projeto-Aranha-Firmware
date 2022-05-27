#include <Arduino.h>
#include <cppQueue.h>

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
    Serial.println("Movement added to queue");
    movementQueue->push(&movement);
}

void ServoController::loop() {
    ServoMovement* movement;
    if (movementQueue->peek(&movement)) {
        if (!movement->getStarted()) {
            Serial.println("Controller starting a movement");
            movement->start();
        }

        moveServo(servo, getCorrectedAngleFor(movement->getAngle()));

        if (movement->getCompleted()) {
            movementQueue->pop(&movement);
            delete movement;
            Serial.println("Movement removed from queue");
        }
    }
}

void ServoController::updateCalibration(byte refAngle) {
    // TODO
}

void ServoController::updateCalibrationFromStoredData() {
    // TODO
}

byte ServoController::getCorrectedAngleFor(byte angle) {
    // TODO: Fix this after calibration
    return angle;
}
