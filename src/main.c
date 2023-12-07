#include "Control.h"
#include <stdio.h>

int main() {
    Device device = {0};
    openDevice(&device);

    interactiveMode(device);

    closeDevice(device);
    return 0;
}
