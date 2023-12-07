#include "Control.h"
#include "Driver.h"
#include "Result.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
All these function will follow a general structure:
1. Create variables to store command and response
2. HANDLE_ERROR will check to make sure all is good
3. assuming no errors, return SUCCESS

Extras will be discussed per function
*/

// After a write, the motor needs 3 seconds, so we sleep for that
// Then, we need to check the write with R4 -> returns 1 if succesffull
Result writeMotorDriverSettings(Device device) {
    unsigned char write_response[64];
    unsigned char write_command[64] = "RW\0";
    HANDLE_ERROR(sendCommandGetResponse(device, write_command, write_response),
                 "Command to write driver settings failed");
    sleep(3);

    unsigned char check_response[64];
    unsigned char check_command[64] = "R4\0";
    HANDLE_ERROR(sendCommandGetResponse(device, check_command, check_response),
                 "Command to check driver write failed");

    if (check_response[0] != '1') {
        HANDLE_ERROR(ARCUS_ERROR,
                     "Write check returned failure, motor will not perform as expected");
    }
    return SUCCESS;
}

Result readMotorDriverSettings(Device device) {
    unsigned char read_response[64];
    unsigned char read_command[64] = "RR\0";
    HANDLE_ERROR(sendCommandGetResponse(device, read_command, read_response),
                 "Command to read driver settings failed");
    sleep(3);

    unsigned char check_response[64];
    unsigned char check_command[64] = "R2\0";
    HANDLE_ERROR(sendCommandGetResponse(device, check_command, check_response),
                 "Command to check driver read failed");

    if (check_response[0] != '1') {
        HANDLE_ERROR(ARCUS_ERROR,
                     "Read check returned failure, driver settings not updated");
    }
    return SUCCESS;
}
// TODO error message
Result setHighSpeed(Device device, int high_speed) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "HSPD=%i", high_speed);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "setHighSpeed");
    return SUCCESS;
}

// TODO error message
Result setLowSpeed(Device device, int low_speed) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "LSPD=%i", low_speed);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "setLowSpeed");
    return SUCCESS;
}

// TODO error message
Result setAccelerationTime(Device device, int accel_time) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "ACC=%i", accel_time);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response),
                 "setAccelerationTime");
    return SUCCESS;
}

// TODO error message
Result setAccelerationProfile(Device device, int profile) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "SCV=%i", profile);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response),
                 "setAccelerationProfile");
    return SUCCESS;
}

// TODO error message
Result setIdleTime(Device device, int idle_time) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "DRVIT=%i", idle_time);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "setIdleTime");
    return SUCCESS;
}

// TODO error message
Result setMicrostepping(Device device, int steps) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "DRVMS=%i", steps);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "setMicrostepping");
    return SUCCESS;
}

// TODO error message
Result setAbsoluteMovement(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "ABS\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response),
                 "setAbsoluteMovement");
    return SUCCESS;
}

// TODO error message
Result setRelativeMovement(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "INC\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response),
                 "setRelativeMovement");
    return SUCCESS;
}

// TODO error message
Result setPosition(Device device, int idle_time) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "PX=%i", idle_time);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "MESSAGE");
    return SUCCESS;
}

// TODO error message
Result getHighSpeed(Device device, int *high_speed) {
    unsigned char response[64];
    unsigned char command[64] = "HSPD\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "MESSAGE");

    *high_speed = strtol((char *)response, (char **)NULL, 10);
    return SUCCESS;
}

// TODO error message
Result getPosition(Device device, int *position) {
    unsigned char response[64];
    unsigned char command[64] = "PX\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "MESSAGE");

    *position = strtol((char *)response, (char **)NULL, 10);
    return SUCCESS;
}

// TODO error message
Result moveStage(Device device, int position) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "X%i", position);

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "MESSAGE");
    return SUCCESS;
}

Result getMotorStatus(Device device, int *status) {
    unsigned char response[64];
    unsigned char command[64] = "MST\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "MESSAGE");

    *status = strtol((char *)response, (char **)NULL, 10);
    return SUCCESS;
}

// TODO error message
Result turnMotorOn(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "EO=1\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "turnMotorOn");
    return SUCCESS;
}
// TODO error message
Result turnMotorOff(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "EO=0\0";

    HANDLE_ERROR(sendCommandGetResponse(device, command, response), "turnMotorOff");
    return SUCCESS;
}
// TODO Error message and write to file
Result waitForMotorIdle(Device device, FILE *file, struct timespec time) {
    int status;
    do {
        HANDLE_ERROR(getMotorStatus(device, &status), "MESSAHE");
    } while (status != 0);
    return SUCCESS;
}

void _toUpperCase(const unsigned char *in_string, unsigned char *out_string) {
    int len = strlen((char *)in_string);
    for (int i = 0; i < len; i++) {
        out_string[i] = toupper(in_string[i]);
    }
}

Result interactiveMode(Device device) {
    unsigned char raw_command[64];
    unsigned char upper_command[64];
    unsigned char response[64];
    printf("Entering interactive mode\n");
    while (1) {
        scanf(" %s", raw_command);
        printf(" %s", raw_command);
        _toUpperCase(raw_command, upper_command);
        HANDLE_ERROR_UNLESS(
            IO_ERROR, sendCommandGetResponse(device, upper_command, response), "MESSAHE");

        if (strcmp((char *)upper_command, "EXIT") == 0) {
            break;
        }

        printf("%s\n", response);
    }
    return SUCCESS;
}
