#include "Calibration.h"
#include <stdio.h>
#include <string.h>

Result getCalibrateParametersFromFile(CalibrateParameters *params) {
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
        } else if (strcmp(variable, "IdleTime") == 0) {
            params->idle_time = value;
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
            params->tolerance = value;
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
    HANDLE_ERROR(setHighSpeed(device, params.high_speed), "CAL HIGH");
    HANDLE_ERROR(setAccelerationTime(device, params.acceleration_time), "cal accel");
    HANDLE_ERROR(setIdleTime(device, params.idle_time), "cal idle");
    HANDLE_ERROR(setMicrostepping(device, 50), "cal mciro");
    HANDLE_ERROR(setIdleTime(device, 1), "cal idle");
    HANDLE_ERROR(writeMotorDriverSettings(device), "cal write");
    HANDLE_ERROR(setPosition(device, 0), "CAL pos");
    return SUCCESS;
}
