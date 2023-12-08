#ifndef CONTROL_H
#define CONTROL_H

#include "Driver.h"
// Setters
Result setHighSpeed(Device device, int high_speed);
Result setLowSpeed(Device device, int low_speed);
Result setAccelerationTime(Device device, int accel_time);
Result setAccelerationProfile(Device device, int profile);
Result setIdleTime(Device device, int idle_time);
Result setMicrostepping(Device device, int steps);
Result setAbsoluteMovement(Device device);
Result setRelativeMovement(Device device);
Result setPosition(Device device, int idle_time);
// Getters
Result getHighSpeed(Device device, int *high_speed);
Result getPosition(Device device, int *position);
Result getMotorStatus(Device device, int *status);

double _getElapsedTime(struct timespec start_time, struct timespec end_time);

// Misc
Result turnMotorOn(Device device);
Result turnMotorOff(Device device);
Result waitForMotorIdle(Device device, FILE *file, struct timespec time);
void _toUpperCase(unsigned char *string);
Result interactiveMode(Device device);
Result writeMotorDriverSettings(Device device);
Result readMotorDriverSettings(Device device);
Result moveStage(Device device, int position);

#endif
