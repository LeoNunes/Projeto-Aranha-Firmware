#include <Arduino.h>

#include <modes/calibratedsingleservomode.h>
#include <commands/commandmanager.h>
#include <commands/commandinterceptor.h>
#include <servo/servocontrollers.h>
#include <servo/instantmovement.h>
#include <util/stringutil.h>
#include <config.h>

void CalibratedSingleServoMode::initiateMode() {
    Serial.println("--- Initiating Calibrated Single Servo Mode ---");
    servoSelected = false;

    interceptorId = COMMAND_MANAGER.addCommandInterceptor(*this);

    Serial.println("Please send a servo number");
}

void CalibratedSingleServoMode::terminateMode() {
    COMMAND_MANAGER.removeCommandInterceptor(interceptorId);
    Serial.println("--- Calibrated Single Servo Mode Terminated ---");
}

void CalibratedSingleServoMode::loop() {
    if (servoSelected) {
        servoController->loop();
    }
}

bool CalibratedSingleServoMode::intercept(String command) {
    if (!isInt(command)) {
        return false;
    }
    if (!servoSelected) {
        int servoNumber = command.toInt();
        if (servoNumber >= SERVO_COUNT) {
            Serial.print("[ERROR] ");
            Serial.print(servoNumber);
            Serial.println(" is not a valid servo. Try a different one");
            return true;
        }
        servoController = SERVO_CONTROLLERS[servoNumber];
        servoSelected = true;
        Serial.print("Servo selected: ");
        Serial.println(servoNumber);
        Serial.println("You can now send values for the angle or 'EXT' to go back to Main Mode");
    } else {
        int angle = command.toInt();
        Serial.print("Sending servo to ");
        Serial.print(angle);
        Serial.println(" degrees");

        servoController->addMovementToQueue(new InstantMovement(angle, 0));
    }
    return true;
}
