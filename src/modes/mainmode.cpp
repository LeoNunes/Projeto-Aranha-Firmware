#include <Arduino.h>

#include <modes/mainmode.h>
#include <servo/servo.h>
#include <servo/legcontrollers.h>
#include <servo/instantmovement.h>
#include <servo/linearmovement.h>


void MainMode::initiateMode() {
    Serial.println("--- Initiating Main Mode ---");
    Serial.println("- Type SSM to enter Single Servo Mode -");
    Serial.println("- Type CAL to enter Calibration Mode -");
    Serial.println("- Type BEH to enter Behavior Mode -");
    Serial.println("- Type MM or EXT or EXIT to return to Main Mode -");

    initializeLegControllers();

    

    // SLEEP POSITION
    FRONT_LEFT_LEG->MoveTo(62, 0, -25);
    FRONT_RIGHT_LEG->MoveTo(62, 0, -25);
    BACK_LEFT_LEG->MoveTo(62, 0, -25);
    BACK_RIGHT_LEG->MoveTo(62, 0, -25);

    // AWAIT
    FRONT_LEFT_LEG->MoveTo(62, 0, -25, 5000);
    FRONT_RIGHT_LEG->MoveTo(62, 0, -25, 5000);
    BACK_LEFT_LEG->MoveTo(62, 0, -25, 5000);
    BACK_RIGHT_LEG->MoveTo(62, 0, -25, 5000);

    // Move to diagonal
    FRONT_LEFT_LEG->MoveTo(55, 55, -25);
    FRONT_RIGHT_LEG->MoveTo(55, 55, -25);
    BACK_LEFT_LEG->MoveTo(55, 55, -25);
    BACK_RIGHT_LEG->MoveTo(55, 55, -25);
    
    // Lift
    FRONT_LEFT_LEG->MoveTo(55, 55, -50);
    FRONT_RIGHT_LEG->MoveTo(55, 55, -50);
    BACK_LEFT_LEG->MoveTo(55, 55, -50);
    BACK_RIGHT_LEG->MoveTo(55, 55, -50);
    
    // Lift More
    // FRONT_LEFT_LEG->MoveTo(55, 55, -100);
    // FRONT_RIGHT_LEG->MoveTo(55, 55, -100);
    // BACK_LEFT_LEG->MoveTo(55, 55, -100);
    // BACK_RIGHT_LEG->MoveTo(55, 55, -100);

    for (int i = 0; i < 3; i++) {

        FRONT_LEFT_LEG->MoveTo(85, 55, -50);
        FRONT_RIGHT_LEG->MoveTo(85, 55, -50);
        BACK_LEFT_LEG->MoveTo(25, 55, -50);
        BACK_RIGHT_LEG->MoveTo(25, 55, -50);

        FRONT_LEFT_LEG->StepTo(25, 55, -50);
        FRONT_RIGHT_LEG->MoveTo(85, 55, -50);
        BACK_LEFT_LEG->MoveTo(25, 55, -50);
        BACK_RIGHT_LEG->MoveTo(25, 55, -50);

        FRONT_LEFT_LEG->MoveTo(25, 55, -50);
        FRONT_RIGHT_LEG->StepTo(25, 55, -50);
        BACK_LEFT_LEG->MoveTo(25, 55, -50);
        BACK_RIGHT_LEG->MoveTo(25, 55, -50);

        FRONT_LEFT_LEG->MoveTo(25, 55, -50);
        FRONT_RIGHT_LEG->MoveTo(25, 55, -50);
        BACK_LEFT_LEG->StepTo(85, 55, -50);
        BACK_RIGHT_LEG->MoveTo(25, 55, -50);

        FRONT_LEFT_LEG->MoveTo(25, 55, -50);
        FRONT_RIGHT_LEG->MoveTo(25, 55, -50);
        BACK_LEFT_LEG->MoveTo(85, 55, -50);
        BACK_RIGHT_LEG->StepTo(85, 55, -50);

        FRONT_LEFT_LEG->MoveTo(55, 55, -50);
        FRONT_RIGHT_LEG->MoveTo(55, 55, -50);
        BACK_LEFT_LEG->MoveTo(55, 55, -50);
        BACK_RIGHT_LEG->MoveTo(55, 55, -50);
    }
}

void MainMode::terminateMode() {
    Serial.println("--- Terminating Main Mode ---");
}


bool step1 = false;
bool step2 = false;

void MainMode::loop() {
    legControllersLoop();

    // TODO: implement Main Mode

}
