#ifndef CALIBRATE_H
#define CALIBRATE_H

#include "Control.h"

typedef struct CalibrateParameters {
    int high_speed;
    int acceleration_time;
    int idle_time;
    int averaging_cycles;
    int amplitude;
    int period;
    int dwell_time;
    int factor;
    int max_speed;
    int tolerance;
} CalibrateParameters;

Result getCalibrateParametersFromFile(CalibrateParameters *params);
Result _prepareDeviceForCalibration(Device device, CalibrateParameters params);

#endif
