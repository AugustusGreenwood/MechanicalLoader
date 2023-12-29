#ifndef DRIVER_H
#define DRIVER_H

#include "result.h"
#include <libusb-1.0/libusb.h>

typedef struct Device {
    struct libusb_context *context;
    struct libusb_device_handle *handle;
    int iface_number;
} Device;
Result _write_to_control(Device device, const int value);
Result _clear_read_buffer(Device device);
Result _flush_device(Device device);
Result _write_to_bulk(Device device, unsigned char command[64]);
Result _read_from_bulk(Device device, unsigned char output[64]);

Result open_device(Device *device);
Result close_device(Device device);
Result send_command_get_response(Device device, unsigned char command[64],
                                 unsigned char response[64]);
#endif
