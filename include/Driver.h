#ifndef DRIVER_H
#define DRIVER_H

#include "Result.h"
#include <libusb-1.0/libusb.h>

typedef struct Device {
    struct libusb_context *context;
    struct libusb_device_handle *handle;
    int iface_number;
} Device;

Result _writeToControl(Device device, const int value);
Result _commandUnderstood(const char *response);
Result _clearReadBuffer(Device device);
Result openDevice(Device *device);
Result readFromBulk(Device device, unsigned char output[64]);
Result writeToBulk(Device device, unsigned char command[64]);
Result closeDevice(Device device);
Result sendCommandGetResponse(Device device, unsigned char command[64],
                              unsigned char response[64]);
Result _flushDevice(Device device);
#endif
