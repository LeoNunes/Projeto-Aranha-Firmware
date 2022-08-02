#include <Arduino.h>

#include <modes/behaviormode.h>
#include <commands/commandmanager.h>
#include <servo/servocontrollers.h>
#include <servo/instantmovement.h>
#include <servo/linearmovement.h>

void BehaviorMode::initiateMode() {
    Serial.println("--- Initiating Behavior Mode ---");
    interceptorId = COMMAND_MANAGER.addCommandInterceptor(*this);
    Serial.println("Type WAKE for the Wake-up routine.");
    Serial.println("Type SLEEP for shutdown routine.");
    Serial.println("Type STORE for legs-up routine.");
}

void BehaviorMode::terminateMode() {
    COMMAND_MANAGER.removeCommandInterceptor(interceptorId);
    Serial.println("--- Behavior Mode Terminated ---");
}

void BehaviorMode::loop() {
    servoControllersLoop();
    //get queue size and lock new commands until behaviour is finished
}

bool BehaviorMode::intercept(String command) {
    if (command == "WAKE") {
        Serial.println("Execute wake mode invoked");
        executeWake(); 
        return true;
    }
    if (command == "SLEEP") {
        Serial.println("Execute sleep mode invoked");
        executeSleep();
        return true;
    }
    if (command == "STORE") {
        Serial.println("Execute store mode invoked");
        executeStore();
        return true;
    }
    return false;
}

void BehaviorMode::executeWake() {
    Serial.println("ExecuteWake started...");
    for (int i = 0; i < 4; i++) {
        InstantMovement* m0_0 = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[3*i+0]->addMovementToQueue(m0_0);
        LinearMovement* m0_1 = new LinearMovement(0, 45, 1000);
        SERVO_CONTROLLERS[3*i+0]->addMovementToQueue(m0_1);

        InstantMovement* m1_0 = new InstantMovement(0, 2000);
        SERVO_CONTROLLERS[3*i+1]->addMovementToQueue(m1_0);
        LinearMovement* m1_1 = new LinearMovement(0, 55, 2000);
        SERVO_CONTROLLERS[3*i+1]->addMovementToQueue(m1_1);

        InstantMovement* m2_0 = new InstantMovement(145, 2000);
        SERVO_CONTROLLERS[3*i+2]->addMovementToQueue(m2_0);
        LinearMovement* m2_1 = new LinearMovement(145, 120, 1000);
        SERVO_CONTROLLERS[3*i+2]->addMovementToQueue(m2_1);
    }
    Serial.println("ExecuteWake finished");
}

void BehaviorMode::executeSleep() {
    Serial.println("ExecuteSleep started...");
    for (int i = 0; i < 4; i++) {
        InstantMovement* m0_0 = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[3*i+0]->addMovementToQueue(m0_0);

        InstantMovement* m1_0 = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[3*i+1]->addMovementToQueue(m1_0);

        InstantMovement* m2_0 = new InstantMovement(145, 1000);
        SERVO_CONTROLLERS[3*i+2]->addMovementToQueue(m2_0);
    }
    Serial.println("ExecuteSleep finished");
}

void BehaviorMode::executeStore() {
    Serial.println("ExecuteSleep started...");
    for (int i = 0; i < 4; i++) {
        InstantMovement* m0_0 = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[3*i+0]->addMovementToQueue(m0_0);

        InstantMovement* m1_0 = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[3*i+1]->addMovementToQueue(m1_0);

        InstantMovement* m2_0 = new InstantMovement(0, 1000);
        SERVO_CONTROLLERS[3*i+2]->addMovementToQueue(m2_0);
    }
    Serial.println("ExecuteSleep finished");
}

