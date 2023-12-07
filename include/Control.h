#ifndef CONTROL_H
#define CONTROL_H

#include "Driver.h"
#include "Result.h"
#include <stdio.h>

Result setHighSpeed(Device device, int high_speed);
Result setLowSpeed(Device device, int low_speed);
Result setAccelerationTime(Device device, int accel_time);
Result setAccelerationProfile(Device device, int profile);
Result setIdleTime(Device device, int idle_time);
Result setMicrostepping(Device device, int steps);
Result setAbsoluteMovement(Device device);
Result setRelativeMovement(Device device);
Result setPosition(Device device, int idle_time);

Result getHighSpeed(Device device, int *high_speed);
Result getPosition(Device device, int *position);
Result getMotorStatus(Device device, int *status);

Result writeMotorDriverSettings(Device device);
Result readMotorDriverSettings(Device device);
Result moveStage(Device device, int position);
// TODO
Result turnMotorOn(Device device);
// TODO
Result turnMotorOff(Device device);
// TODO
Result waitForMotorIdle(Device device, FILE *file, struct timespec time);
Result interactiveMode(Device device);

#endif
