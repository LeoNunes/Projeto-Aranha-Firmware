#include <Arduino.h>

#include <modes/calibrationmode.h>
#include <commands/commandmanager.h>
#include <servo/servocontrollers.h>
#include <util/stringutil.h>
#include <config.h>

void CalibrationMode::initiateMode() {
    Serial.println("--- Initiating Calibration Mode ---");
    Serial.println("You should use the SingleServoMode to get the correct values for 0 and 90 degrees for each servo before using this mode.");
    interceptorId = COMMAND_MANAGER.addCommandInterceptor(*this);
    restartMode();
}

void CalibrationMode::restartMode() {
    servoSelected = false;
    zeroAngleSelected = false;
    zeroAngle = 0;
    ninetyAngleSelected = false;
    ninetyAngle = 0;

    Serial.print("Please enter a number between 0 and ");
    Serial.print(SERVO_COUNT - 1);
    Serial.println(" to select the servo for calibration.");
    Serial.println("Use READ to get all calibration data or use RESET to reset calibration data for all servos");
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
        return interceptForGettingServo(command);
    }
    if (!zeroAngleSelected) {
        return interceptForGettingZeroAngle(command);
    }
    if (!ninetyAngleSelected) {
        return interceptForGettingNinetyAngle(command);
    }
    return interceptForCommit(command);
}

bool CalibrationMode::interceptForGettingServo(String command) {
    if (command == "READ") {
        readAllCalibration();
        return true;
    }
    if (command == "RESET") {
        resetAllCalibration();
        return true;
    }
    if (!isInt(command)) {
        return false;
    }
    int servoNumber = command.toInt();
    if (servoNumber >= SERVO_COUNT) {
        Serial.print("[ERROR] ");
        Serial.print(servoNumber);
        Serial.println(" is not a valid servo.");
        return true;
    }
    servo = ALL_SERVOS[servoNumber];
    servoSelected = true;
    Serial.print("Servo selected: ");
    Serial.println(servo);
    Serial.println("Enter the value for the zero degree angle (the raw servo position where it is in the reference zero degree).");
    return true;
}

bool CalibrationMode::interceptForGettingZeroAngle(String command) {
    if (!isInt(command)) {
        return false;
    }
    int angle = command.toInt();
    if (angle < 0 || angle > 180) {
        Serial.print("[ERROR] ");
        Serial.print(angle);
        Serial.println(" is not a valid angle.");
        return true;
    }
    zeroAngle = angle;
    zeroAngleSelected = true;
    Serial.print("Zero angle selected: ");
    Serial.println(zeroAngle);
    Serial.println("Enter the value for the ninety degrees angle (the raw servo position where it is in the reference ninety degrees).");
    return true;
}

bool CalibrationMode::interceptForGettingNinetyAngle(String command) {
    if (!isInt(command)) {
        return false;
    }
    int angle = command.toInt();
    if (angle < 0 || angle > 180) {
        Serial.print("[ERROR] ");
        Serial.print(angle);
        Serial.println(" is not a valid angle.");
        return true;
    }
    ninetyAngle = angle;
    ninetyAngleSelected = true;
    Serial.print("Ninety degrees angle selected: ");
    Serial.println(ninetyAngle);
    Serial.println("Enter COMMIT to save the data.");
    return true;
}

bool CalibrationMode::interceptForCommit(String command) {
    if (command == "COMMIT") {
        SERVO_CONTROLLERS[servo]->updateCalibration(zeroAngle, ninetyAngle);
        Serial.println("Calibration stored successfully. Restarting calibration mode.");
        restartMode();
        return true;
    }

    return false;
}

void CalibrationMode::readAllCalibration() {
    Serial.println("Reading calibration data for all servos.");
    for (int i = 0; i < SERVO_COUNT; i++) {
        auto [zero, ninety] = SERVO_CONTROLLERS[i]->getCalibration();
        Serial.print("Servo: ");
        Serial.print(i);
        Serial.print(". Zero degree: ");
        Serial.print(zero);
        Serial.print(". Ninety degree: ");
        Serial.print(ninety);
        Serial.println(".");
    }
}

void CalibrationMode::resetAllCalibration() {
    Serial.println("Reseting calibration for all Servos.");
    for (int i = 0; i < SERVO_COUNT; i++) {
        SERVO_CONTROLLERS[i]->resetCalibration();
    }
    Serial.println("Calibration data reseted for all Servos.");
    Serial.println("You can now select a servo number to calibrate it.");
}
