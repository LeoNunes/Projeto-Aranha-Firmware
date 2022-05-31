#include <Arduino.h>

#include <util/stringutil.h>

bool isInt(String string) {
    for (char c : string) {
        if (c - '0' < 0 || c - '0' > 9) {
            return false;
        }
    }
    return true;
}