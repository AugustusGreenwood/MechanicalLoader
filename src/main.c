#include "Driver.h"
#include "Result.h"

int main() {
    Device device = {0};
    openDevice(&device);
    if (device.handle == NULL) {
        return 0;
    }
    unsigned char response[64];
    unsigned char command[64] = "HSPD";
    sendCommandGetResponse(device, command, response);
    closeDevice(device);
    return 0;
}
