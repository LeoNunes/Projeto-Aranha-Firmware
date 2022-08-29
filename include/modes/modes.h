#pragma once

#include <modes/modemanager.h>
#include <modes/mainmode.h>
#include <modes/singleservomode.h>
#include <modes/calibratedsingleservomode.h>
#include <modes/calibrationmode.h>
#include <modes/behaviormode.h>

inline ModeManager MODE_MANAGER = ModeManager();
inline MainMode MAIN_MODE = MainMode();
inline SingleServoMode SINGLE_SERVO_MODE = SingleServoMode();
inline CalibratedSingleServoMode CALIBRATED_SINGLE_SERVO_MODE = CalibratedSingleServoMode();
inline CalibrationMode CALIBRATION_MODE = CalibrationMode();
inline BehaviorMode BEHAVIOR_MODE = BehaviorMode();
