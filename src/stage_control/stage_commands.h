#ifndef COMMANDS_H
#define COMMANDS_H

#include "stage_driver.h"

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

// Misc
Result turnMotorOn(Device device);
Result turnMotorOff(Device device);
// Result waitForMotorIdle(Device device, FILE *file, const struct timespec start_time,
//                        struct timespec *current_time);
Result interactiveMode(Device device);
Result writeMotorDriverSettings(Device device);
Result readMotorDriverSettings(Device device);
Result moveStage(Device device, int position);
/*
 * Open to better possiblities for all the time but currently it is like this to prevent
 * always initializing time varaible to hopefully be quicker?
 */
Result runCycle(Device device, int distance, struct timespec start_time, FILE *file,
                struct timespec *current_time, struct timespec *start_cycle_time,
                struct timespec *end_cycle_time, double *elapsed_time);
#endif
