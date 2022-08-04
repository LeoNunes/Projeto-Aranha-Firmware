#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#include <servo/servo.h>
#include <config.h>

#define SERVOMIN 80  // Minimum value
#define SERVOMAX 600 // Maximum value

Adafruit_PWMServoDriver pca9685;
bool pca9685_Initialized = false;

void initializePCA9685(uint8_t addr) {
    pca9685 = Adafruit_PWMServoDriver(addr);

    pca9685.begin();
    pca9685.setPWMFreq(50);

    pca9685_Initialized = true;
}

void  moveServo(Servo servo, int angle) {
    if (!pca9685_Initialized) {
        Serial.println("[ERROR] PCA9685 driver was not initialized");
        return;
    }

    if (angle < 0 || angle > 180) {
        Serial.print("[ERROR] ");
        Serial.print(angle);
        Serial.println("degrees is invalid for the servo angle");
        return;
    }

    int pwm = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pca9685.setPWM(SERVOS_PINS[servo], 0, pwm);
}
