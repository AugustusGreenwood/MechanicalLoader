#include "stage_control.h"

int main() {
    Device device = {0};
    openDevice(&device);
    closeDevice(device);
    return 0;
}
