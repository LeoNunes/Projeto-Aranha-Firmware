#include <Arduino.h>

#include <serialcommands/baseserialcommandinterceptor.h>
#include <modes/modes.h>

bool BaseSerialCommandInterceptor::intercept(String command) {
    if (command == "EXT" || command == "EXIT" || command == "MM") {
        MODE_MANAGER.setMode(MAIN_MODE);
        return true;
    } 
    if (command == "SSM") {
        MODE_MANAGER.setMode(SINGLE_SERVO_MODE);
        return true;
    } 
    return false;
}