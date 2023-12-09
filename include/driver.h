#ifndef DRIVER_H
#define DRIVER_H

#include "Result.h"
#include <libusb-1.0/libusb.h>

typedef struct Device {
    struct libusb_context *context;
    struct libusb_device_handle *handle;
    int iface_number;
} Device;

Result openDevice(Device *device);
Result closeDevice(Device device);
Result sendCommandGetResponse(Device device, unsigned char command[64],
                              unsigned char response[64]);
#endif
