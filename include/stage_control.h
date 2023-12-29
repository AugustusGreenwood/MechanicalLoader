#ifndef STAGE_CONTROL_H
#define STAGE_CONTROL_H

#include "result.h"

// DRIVER
typedef struct Device {
    struct libusb_context *context;
    struct libusb_device_handle *handle;
    int iface_number;
} Device;
Result open_device(Device *device);
Result close_device(Device device);
Result send_command_get_response(Device device, unsigned char command[64],
                                 unsigned char response[64]);
// COMMANDS
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

// CALIBRATION
typedef struct CalibrateParameters CalibrateParameters;

#endif
