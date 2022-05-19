#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <serialcommand.h>

#define SERVOMIN 80  // Minimum value
#define SERVOMAX 600 // Maximum value

// Define servo motor connections (expand as required)
#define SER0 0 // Servo Motor 0 on connector 0
#define SER1 1 // Servo Motor 1 on connector 1
#define SER2 2 // Servo Motor 2 on connector 2

// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;
int pwm2;

// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

void setup()
{
    Serial.begin(115200);

    Serial.println("Servo calibration");

    pca9685.begin();
    pca9685.setPWMFreq(50);
}

void loop()
{
    String command = readSerialCommand();
    if (command != "") {
        int value = command.toInt();

        // Determine PWM pulse width
        pwm0 = map(value, 0, 180, SERVOMIN, SERVOMAX);
        // Write to PCA9685
        pca9685.setPWM(SER0, 0, pwm0);
        // Print to serial monitor
        Serial.print("Motor 0 = ");
        Serial.println(value);
        delay(30);
    }
}
