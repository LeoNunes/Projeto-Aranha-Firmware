#include <Arduino.h>

#include <modes/singleservomode.h>
#include <serialcommands/serialcommandmanager.h>
#include <serialcommands/serialcommandinterceptor.h>
#include <servo/servo.h>

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
            return true;
        }
        servo = ALL_SERVOS[servoNumber];
        servoSelected = true;
        Serial.print("Servo selected: ");
        Serial.println(servo);
        Serial.println("You can now send values for the angle or 'EXT' to go back to Main Mode");
    } else {
        int angle = command.toInt();
        Serial.print("Sending servo ");
        Serial.print(servo);
        Serial.print(" to ");
        Serial.print(angle);
        Serial.println(" degrees");
        moveServo(servo, angle);
    }
    return true;
}