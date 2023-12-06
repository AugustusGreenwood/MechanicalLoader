#include "Driver.h"
#include "Result.h"

const int TIMEOUT = 1000;
const int VENDOR_ID = 0x1589;
const int PRODUCT_ID = 0xa101;

Result _writeToControl(Device device, const int value) {
    HANDLE_ERROR(
        libusb_control_transfer(device.handle, 0x40, 0x02, value, 0x00, NULL, 0, TIMEOUT),
        "Failed to write to control with libusb error");
    return SUCCESS;
}

Result _commandUnderstood(const char *response) {
    if (response[0] == '?') {
        return BAD_COMMAND;
    }
    return SUCCESS;
}

Result _clearReadBuffer(Device device) {
    unsigned char _buffer[4096];
    int transferred;
    HANDLE_ERROR(libusb_bulk_transfer(device.handle, 0x82, _buffer, sizeof(_buffer),
                                      &transferred, TIMEOUT),
                 "Failed to clear read buffer with libusb error");

    return SUCCESS;
}

Result openDevice(Device *device) {
    HANDLE_ERROR(libusb_init(&device->context),
                 "Failed to initialize libusb library, restart program");

    libusb_device **list;
    int num_devices = libusb_get_device_list(device->context, &list);

    struct libusb_device_descriptor descriptor;
    for (int i = 0; i < num_devices; i++) {
        HANDLE_ERROR(libusb_get_device_descriptor(list[i], &descriptor),
                     "Failed to get descriptor for some connected device");

        if ((descriptor.idProduct == PRODUCT_ID) && (descriptor.idVendor == VENDOR_ID)) {
            HANDLE_ERROR(libusb_open(list[i], &device->handle),
                         "Device found but failed to successfully open");

            HANDLE_ERROR(libusb_claim_interface(device->handle, device->iface_number),
                         "Device found, opened, but claiming interface failed");

            HANDLE_ERROR(_writeToControl(*device, 0x02),
                         "Device found, opened with libusb, interface claimed but failed "
                         "to write open command to control endpoint");

            HANDLE_ERROR_UNLESS(TIMEOUT_ERROR, _clearReadBuffer(*device),
                                "Failed to clear read buffer after opening");

            return SUCCESS;
        }
    }
    libusb_free_device_list(list, 1);

    HANDLE_ERROR(NOT_FOUND_ERROR, "All devices successfully iterated but specified "
                                  "vendor and product ids not found");
}

Result readFromBulk(Device device, unsigned char output[64]) {
    int amt_read;
    HANDLE_ERROR(libusb_bulk_transfer(device.handle, 0x82, output, 8, &amt_read, TIMEOUT),
                 "Failed to read from bulk with libusb error");

    return SUCCESS;
}

Result writeToBulk(Device device, unsigned char command[64]) {
    int amt_written;
    HANDLE_ERROR(
        libusb_bulk_transfer(device.handle, 0x02, command, 8, &amt_written, TIMEOUT),
        "Failed to write to bulk with libusb error");

    if (amt_written != 8) {
        HANDLE_ERROR(IO_ERROR, "Amount written to bulk was incorrect");
    }
    return SUCCESS;
}

Result closeDevice(Device device) {
    HANDLE_ERROR(_writeToControl(device, 0x04),
                 "Failed to send close command to control endpoint.");

    HANDLE_ERROR(libusb_release_interface(device.handle, device.iface_number),
                 "Failed to release device interface");

    libusb_close(device.handle);
    return SUCCESS;
}

Result sendCommandGetResponse(Device device, unsigned char command[64],
                              unsigned char response[64]) {
    HANDLE_ERROR(writeToBulk(device, command), "Failed to write command to bulk");
    HANDLE_ERROR(readFromBulk(device, response), "Failed to read response from bulk");
    return SUCCESS;
}

Result _flushDevice(Device device) {
    HANDLE_ERROR(_writeToControl(device, 0x01),
                 "Failed to send flush command to control");
    return SUCCESS;
}

void thing() {}
