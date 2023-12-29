#ifndef COMMANDS_H
#define COMMANDS_H

#include "driver.h"
#include <time.h>

typedef struct timespec timespec;
void _to_upper_case(unsigned char *string);
Result set_high_speed(Device device, int high_speed);
Result set_low_speed(Device device, int low_speed);
Result set_acceleration_time(Device device, int accel_time);
Result set_acceleration_profile(Device device, int profile);
Result set_idle_time(Device device, int idle_time);
Result set_microstepping(Device device, int steps);
Result set_absolute_movement(Device device);
Result set_relative_movement(Device device);
Result set_position(Device device, int position);
Result get_high_speed(Device device, int *high_speed);
Result get_position(Device device, int *position);
Result get_motor_status(Device device, int *status);
Result turn_motor_on(Device device);
Result turn_motor_off(Device device);
Result interactive_mode(Device device);
Result write_motor_driver_settings(Device device);
Result read_motor_driver_settings(Device device);
Result move_stage(Device device, int position);
Result wait_for_motor_idle(Device device, const timespec start_time, FILE *file);
Result move_cycle(Device device, const int amplitude, timespec *start_time, FILE *file);

#endif
