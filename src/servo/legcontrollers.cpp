#include <servo/legcontrollers.h>
#include <servo/servocontrollers.h>
#include <config.h>

void initializeLegControllers() {
    initializeServoControllers();
    FRONT_LEFT_LEG = new LegController(
        SERVO_CONTROLLERS[SER_FL_1],
        SERVO_CONTROLLERS[SER_FL_2],
        SERVO_CONTROLLERS[SER_FL_3]
    );

    FRONT_RIGHT_LEG = new LegController(
        SERVO_CONTROLLERS[SER_FR_1],
        SERVO_CONTROLLERS[SER_FR_2],
        SERVO_CONTROLLERS[SER_FR_3]
    );

    BACK_LEFT_LEG = new LegController(
        SERVO_CONTROLLERS[SER_BL_1],
        SERVO_CONTROLLERS[SER_BL_2],
        SERVO_CONTROLLERS[SER_BL_3]
    );

    BACK_RIGHT_LEG = new LegController(
        SERVO_CONTROLLERS[SER_BR_1],
        SERVO_CONTROLLERS[SER_BR_2],
        SERVO_CONTROLLERS[SER_BR_3]
    );
}
