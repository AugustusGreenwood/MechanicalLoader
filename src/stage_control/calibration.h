#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "result.h"

typedef struct CalibrateParameters {
    int high_speed;
    int acceleration_time;
    int averaging_cycles;
    int amplitude;
    int period;
    int dwell_time;
    int factor;
    int max_speed;
    int tolerance;
    int sin_curve;
} CalibrateParameters;

#endif
