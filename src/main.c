#include "stage_commands.h"
#include "stage_control.h"
#include "stage_driver.h"

int main() {
    Device device = {0};
    openDevice(&device);

    interactiveMode(device);

    closeDevice(device);
    return 0;
}
