#ifndef COMMANDS_H
#define COMMANDS_H

#include "driver_p.h"

void _toUpperCase(unsigned char *string);
Result setHighSpeed(Device device, int high_speed);
Result setLowSpeed(Device device, int low_speed);
Result setAccelerationTime(Device device, int accel_time);
Result setAccelerationProfile(Device device, int profile);
Result setIdleTime(Device device, int idle_time);
Result setMicrostepping(Device device, int steps);
Result setAbsoluteMovement(Device device);
Result setRelativeMovement(Device device);
Result setPosition(Device device, int position);
Result getHighSpeed(Device device, int *high_speed);
Result getPosition(Device device, int *position);
Result getMotorStatus(Device device, int *status);
Result turnMotorOn(Device device);
Result turnMotorOff(Device device);
Result interactiveMode(Device device);
Result writeMotorDriverSettings(Device device);
Result readMotorDriverSettings(Device device);
Result moveStage(Device device, int position);

#endif
