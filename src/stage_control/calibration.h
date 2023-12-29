#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <stage_commands.h>

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
    int sin_curve;
} CalibrateParameters;

Result _getCalibrateParametersFromFile(CalibrateParameters *params);
Result _prepareDeviceForCalibration(Device device, CalibrateParameters params);

#endif
