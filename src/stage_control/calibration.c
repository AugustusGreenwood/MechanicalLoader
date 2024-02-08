#include "calibration.h"
#include "commands.h"
#include "result.h"
#include <bits/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

Result _get_calibrate_parameters_from_file(CalibrateParameters *params) {
    FILE *file = fopen("./CalibrateInput.txt", "r");
    char buffer[96];
    char variable[96];
    int value;

    int line = 1;
    while (fgets(buffer, 96, file) != NULL) {
        if (sscanf(buffer, "%s %i\n", variable, &value) != 2) {
            char error_out[96];
            sprintf(error_out, "Was unable to parse line %i\n", line);
            HANDLE_ERROR(INPUT_ERROR, error_out);
        }

        if (strcmp(variable, "HighSpeed") == 0) {
            params->high_speed = value;
        } else if (strcmp(variable, "AccelerationTime") == 0) {
            params->acceleration_time = value;
        } else if (strcmp(variable, "AveragingCycles") == 0) {
            params->averaging_cycles = value;
        } else if (strcmp(variable, "Amplitude") == 0) {
            params->amplitude = value;
        } else if (strcmp(variable, "Period") == 0) {
            params->period = value;
        } else if (strcmp(variable, "DwellTime") == 0) {
            params->dwell_time = value;
        } else if (strcmp(variable, "Factor") == 0) {
            params->factor = value;
        } else if (strcmp(variable, "MaxSpeed") == 0) {
            params->max_speed = value;
        } else if (strcmp(variable, "Tolerance") == 0) {
            if (value >= 1) {
                HANDLE_ERROR(INPUT_ERROR, "invalied tolerance level");
            }
            params->tolerance = value;
        } else if (strcmp(variable, "SCurve") == 0) {
            if (value != 0 && value != 1) {
                HANDLE_ERROR(INPUT_ERROR, "Incorrect scrve arguemnt");
            }
            params->sin_curve = value;
        } else {
            char error_out[96];
            sprintf(error_out, "Was unable to read line %i. Variable was read as %s\n",
                    line, variable);
            HANDLE_ERROR(INPUT_ERROR, error_out);
        }
        line++;
    }
    fclose(file);
    return SUCCESS;
}

// TODO error messages
Result _prepareDeviceForCalibration(Device device, CalibrateParameters params) {
    HANDLE_ERROR(set_high_speed(device, params.high_speed), "CAL HIGH");
    HANDLE_ERROR(set_acceleration_time(device, params.acceleration_time), "cal accel");
    HANDLE_ERROR(set_acceleration_profile(device, params.sin_curve), "cal scurve");
    HANDLE_ERROR(set_microstepping(device, 50), "cal mciro");
    HANDLE_ERROR(set_idle_time(device, 1), "cal idle");
    HANDLE_ERROR(write_motor_driver_settings(device), "cal write");
    HANDLE_ERROR(set_position(device, 0), "CAL pos");
    return SUCCESS;
}

double _get_time_vector_average(double *times, int length) {
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += times[i];
    }
    return sum / length;
}

Result _sin_calibration(Device device, CalibrateParameters params) {
    FILE *file = fopen("cal_temp.txt", "w");
    if (file == NULL) {
        printf("COUDLNT OPEN FILE");
    }
    struct timespec time;

    struct timespec cycle_time;
    double start_time, times[params.averaging_cycles], period, max_time, min_time;
    max_time = (1 + params.tolerance) * params.period;
    min_time = params.tolerance * params.period;
    do {
        for (int cycle = 0; cycle < params.averaging_cycles; cycle++) {
            clock_gettime(CLOCK_MONOTONIC, &cycle_time);
            start_time = cycle_time.tv_sec + cycle_time.tv_nsec / 1e9;
            move_cycle(device, params.amplitude, &time, file);
            clock_gettime(CLOCK_MONOTONIC, &cycle_time);
            times[cycle] = (cycle_time.tv_sec + cycle_time.tv_nsec / 1e9) - start_time;
        }
        period = _get_time_vector_average(times, params.averaging_cycles);
    } while (period > max_time || period < min_time);
    return SUCCESS;
}
