#ifndef DRIVER_H
#define DRIVER_H

#include "result_p.h"
#include <libusb-1.0/libusb.h>

typedef struct Device {
    struct libusb_context *context;
    struct libusb_device_handle *handle;
    int iface_number;
} Device;
Result _writeToControl(Device device, const int value);
Result _commandUnderstood(const unsigned char *response);
Result _clearReadBuffer(Device device);
Result _flushDevice(Device device);
Result _writeToBulk(Device device, unsigned char command[64]);
Result _readFromBulk(Device device, unsigned char output[64]);

Result openDevice(Device *device);
Result closeDevice(Device device);
Result sendCommandGetResponse(Device device, unsigned char command[64],
                              unsigned char response[64]);
#endif
