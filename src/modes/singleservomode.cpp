#include <Arduino.h>

#include <serialcommands/commandmanager.h>
#include <serialcommands/commandinterceptor.h>
#include <modes/singleservomode.h>
#include <servo.h>

void SingleServoMode::initiateMode() {
    Serial.println("--- Initiating Single Servo Mode ---");
    servoSelected = false;

    interceptorId = COMMAND_MANAGER.addCommandInterceptor(*this);

    Serial.println("Please send a servo number");
}

void SingleServoMode::terminateMode() {
    COMMAND_MANAGER.removeCommandInterceptor(interceptorId);
    Serial.println("--- Single Servo Mode Terminated ---");
}

void SingleServoMode::loop() {
    // Do nothing
}

bool SingleServoMode::intercept(String command) {
    if (!servoSelected) {
        int servoNumber = command.toInt();
        if (servoNumber >= SERVO_COUNT) {
            Serial.print("[ERROR] ");
            Serial.print(servoNumber);
            Serial.println(" is not a valid servo. Try a different one");
        }
        servo = ALL_SERVOS[servoNumber];
        servoSelected = true;
        Serial.print("Servo selected: ");
        Serial.println(servo);
        Serial.println("You can now send values for the angle or 'EXT' to go back to Main Mode");
    } else {
        int angle = command.toInt();
        moveServo(servo, angle);
    }
    return true;
}