#include <Arduino.h>

#include <modes/calibrationmode.h>
#include <serialcommands/serialcommandmanager.h>
#include <servo/servo.h>
#include <servo/servocontrollers.h>

void CalibrationMode::initiateMode() {
    Serial.println("--- Initiating Calibration Mode ---");
    interceptorId = COMMAND_MANAGER.addCommandInterceptor(*this);
    restartMode();
}

void CalibrationMode::restartMode() {
    servoSelected = false;
    angleSelected = false;
    selectedAngle = 0;

    Serial.println("Commands:");
    Serial.print(" - A number between 0 and ");
    Serial.print(SERVO_COUNT - 1);
    Serial.println(" to select the servo for calibration");

    Serial.println(" - RESET to reset calibration data for all servos");
}

void CalibrationMode::terminateMode() {
    COMMAND_MANAGER.removeCommandInterceptor(interceptorId);
    Serial.println("--- Calibration Mode Terminated ---");
}

void CalibrationMode::loop() {
    // Do nothing
}

bool CalibrationMode::intercept(String command) {
    if (!servoSelected) {
        return interceptForServoNotSelected(command);
    } else {
        if (!angleSelected) {
            return interceptForServoSelectedAndAngleNotSelected(command);
        }
        else {
            return interceptForServoAndAngleSelected(command);
        }
    }
}

void CalibrationMode::resetAllCalibration() {
    Serial.println("Reseting calibration for all Servos.");
    for (int i = 0; i < SERVO_COUNT; i++) {
        SERVO_CONTROLLERS[i]->resetCalibration();
    }
    Serial.println("Calibration reseted for all Servos.");
    Serial.println("You can now select a servo number to calibrate it.");
}

bool CalibrationMode::interceptForServoNotSelected(String command) {
    if (command == "RESET") {
        resetAllCalibration();
        return true;
    }
    int servoNumber = command.toInt();
    if (servoNumber >= SERVO_COUNT) {
        Serial.print("[ERROR] ");
        Serial.print(servoNumber);
        Serial.println(" is not a valid servo. Try a different one.");
        return true;
    }
    selectedServo = ALL_SERVOS[servoNumber];
    servoSelected = true;
    Serial.print("Servo selected: ");
    Serial.println(selectedServo);
    Serial.println("You can now send values for the angle to move the servo. Adjust it so it is in the correct position");
    Serial.println("Once you get to the reference position, send SELECT to select the value as the reference value.");
    return true;
}

bool CalibrationMode::interceptForServoSelectedAndAngleNotSelected(String command) {
    if (command == "SELECT") {
        Serial.println("Angle selected. Now enter 1 if servo was reversed. Send 0 otherwise");
        angleSelected = true;
        return true;
    }

    int angle = command.toInt();
    if (angle < 0 || angle > 180) {
        Serial.print("[ERROR] ");
        Serial.print(angle);
        Serial.println(" is not a valid angle. Try a different one.");
        return true;
    }
    selectedAngle = angle;
    Serial.print("Sending servo ");
    Serial.print(selectedServo);
    Serial.print(" to ");
    Serial.print(angle);
    Serial.println(" degrees");
    moveServo(selectedServo, angle);
    return true;
}

bool CalibrationMode::interceptForServoAndAngleSelected(String command) {
    bool reversed = (bool)command.toInt();
    SERVO_CONTROLLERS[selectedServo]->updateCalibration(reversed, selectedAngle);

    Serial.println("Calibration stored successfully. Restarting calibration mode.");

    restartMode();
    return true;
}
