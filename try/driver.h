#ifndef DRIVER_H
#define DRIVER_H

#include "result.h"
#include <libusb-1.0/libusb.h>

typedef struct Device {
    struct libusb_context *context;
    struct libusb_device_handle *handle;
    int iface_number;
} Device;

Result open_device(Device *device);
Result close_device(Device device);
Result send_command_get_response(Device device, unsigned char command[64],
                                 unsigned char response[64]);
#endif
