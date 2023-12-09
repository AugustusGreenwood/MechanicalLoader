#include "Calibrate.h"

int main() {
    Device device = {0};
    openDevice(&device);

    interactiveMode(device);

    CalibrateParameters params;
    getCalibrateParametersFromFile(&params);
    _prepareDeviceForCalibration(device, params);

    interactiveMode(device);

    closeDevice(device);
}
