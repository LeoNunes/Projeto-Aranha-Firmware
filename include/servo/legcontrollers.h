#pragma once

#include <Arduino.h>

#include <servo/legcontroller.h>

const byte LEGS_COUNT = 4;

inline LegController* FRONT_LEFT_LEG;
inline LegController* FRONT_RIGHT_LEG;
inline LegController* BACK_LEFT_LEG;
inline LegController* BACK_RIGHT_LEG;

void initializeLegControllers();
