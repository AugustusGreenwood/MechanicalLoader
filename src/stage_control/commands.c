#include "commands.h"
#include "result.h"
#include <bits/time.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// TODO error message
Result set_high_speed(Device device, int high_speed) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "HSPD=%i", high_speed);

    HANDLE_ERROR(send_command_get_response(device, command, response), "setHighSpeed");
    return SUCCESS;
}

// TODO error message
Result set_low_speed(Device device, int low_speed) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "LSPD=%i", low_speed);

    HANDLE_ERROR(send_command_get_response(device, command, response), "setLowSpeed");
    return SUCCESS;
}

// TODO error message
Result set_acceleration_time(Device device, int accel_time) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "ACC=%i", accel_time);

    HANDLE_ERROR(send_command_get_response(device, command, response),
                 "setAccelerationTime");
    return SUCCESS;
}

// TODO error message
Result set_acceleration_profile(Device device, int profile) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "SCV=%i", profile);

    HANDLE_ERROR(send_command_get_response(device, command, response),
                 "setAccelerationProfile");
    return SUCCESS;
}

// TODO error message
Result set_idle_time(Device device, int idle_time) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "DRVIT=%i", idle_time);

    HANDLE_ERROR(send_command_get_response(device, command, response), "setIdleTime");
    return SUCCESS;
}

// TODO error message
Result set_microstepping(Device device, int steps) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "DRVMS=%i", steps);

    HANDLE_ERROR(send_command_get_response(device, command, response),
                 "setMicrostepping");
    return SUCCESS;
}

// TODO error message
Result set_absolute_movement(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "ABS\0";

    HANDLE_ERROR(send_command_get_response(device, command, response),
                 "setAbsoluteMovement");
    return SUCCESS;
}

// TODO error message
Result set_relative_movement(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "INC\0";

    HANDLE_ERROR(send_command_get_response(device, command, response),
                 "setRelativeMovement");
    return SUCCESS;
}

// TODO error message
Result set_position(Device device, int position) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "PX=%i", position);

    HANDLE_ERROR(send_command_get_response(device, command, response), "MESSAGE");
    return SUCCESS;
}

// TODO error message
Result get_high_speed(Device device, int *high_speed) {
    unsigned char response[64];
    unsigned char command[64] = "HSPD\0";

    HANDLE_ERROR(send_command_get_response(device, command, response), "MESSAGE");

    *high_speed = strtol((char *)response, (char **)NULL, 10);
    return SUCCESS;
}

// TODO error message
Result get_position(Device device, int *position) {
    unsigned char response[64];
    unsigned char command[64] = "PX\0";

    HANDLE_ERROR(send_command_get_response(device, command, response), "MESSAGE");

    *position = strtol((char *)response, (char **)NULL, 10);
    return SUCCESS;
}

Result get_motor_status(Device device, int *status) {
    unsigned char response[64];
    unsigned char command[64] = "MST\0";

    HANDLE_ERROR(send_command_get_response(device, command, response), "MESSAGE");

    *status = strtol((char *)response, (char **)NULL, 10);
    return SUCCESS;
}

// TODO error message
Result turn_motor_on(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "EO=1\0";

    HANDLE_ERROR(send_command_get_response(device, command, response), "turnMotorOn");
    return SUCCESS;
}

// TODO error message
Result turn_motor_off(Device device) {
    unsigned char response[64];
    unsigned char command[64] = "EO=0\0";

    HANDLE_ERROR(send_command_get_response(device, command, response), "turnMotorOff");
    return SUCCESS;
}

void _to_upper_case(unsigned char *string) {
    for (unsigned long i = 0; i < strlen((char *)string); i++) {
        string[i] = toupper(string[i]);
    }
}

// TODO error message
Result interactive_mode(Device device) {
    unsigned char command[64];
    unsigned char response[64];
    printf("Entering interactive mode\n");
    while (scanf(" %s", command) == 1) {
        _to_upper_case(command);

        if (strcmp((char *)command, "EXIT") == 0) {
            break;
        }

        // Taken from a very nice person on reddit
        // https://www.reddit.com/r/C_Programming/comments/502xun/how_do_i_clear_a_line_on_console_in_c/
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line

        send_command_get_response(device, command, response);

        printf("%s --> %s\n", command, response);
    }
    return SUCCESS;
}

// After a write, the motor needs 3 seconds, so we sleep for that
// Then, we need to check the write with R4 -> returns 1 if succesffull
Result write_motor_driver_settings(Device device) {
    unsigned char write_response[64];
    unsigned char write_command[64] = "RW\0";
    HANDLE_ERROR(send_command_get_response(device, write_command, write_response),
                 "Command to write driver settings failed");
    sleep(3);

    unsigned char check_response[64];
    unsigned char check_command[64] = "R4\0";
    HANDLE_ERROR(send_command_get_response(device, check_command, check_response),
                 "Command to check driver write failed");

    if (check_response[0] != '1') {
        HANDLE_ERROR(ARCUS_ERROR,
                     "Write check returned failure, motor will not perform as expected");
    }
    return SUCCESS;
}

Result read_motor_driver_settings(Device device) {
    unsigned char read_response[64];
    unsigned char read_command[64] = "RR\0";
    HANDLE_ERROR(send_command_get_response(device, read_command, read_response),
                 "Command to read driver settings failed");
    sleep(3);

    unsigned char check_response[64];
    unsigned char check_command[64] = "R2\0";
    HANDLE_ERROR(send_command_get_response(device, check_command, check_response),
                 "Command to check driver read failed");

    if (check_response[0] != '1') {
        HANDLE_ERROR(ARCUS_ERROR,
                     "Read check returned failure, driver settings not updated");
    }
    return SUCCESS;
}

// TODO error message
Result move_stage(Device device, int position) {
    unsigned char response[64];
    unsigned char command[64];
    sprintf((char *)command, "X%i", position);

    HANDLE_ERROR(send_command_get_response(device, command, response), "MESSAGE");
    return SUCCESS;
}

double _get_elapsed_seconds(const timespec start, const timespec now) {
    return (now.tv_sec - start.tv_sec) + (now.tv_nsec - start.tv_nsec) / 1e9;
}

// TODO error messagesj
Result wait_for_motor_idle(Device device, const timespec start_time, FILE *file) {
    int motor_status;
    if (file == NULL) {
        do {
            HANDLE_ERROR(get_motor_status(device, &motor_status), "MESSAGE");
        } while (motor_status != 0);
    } else {
        int position;
        timespec now;
        do {
            clock_gettime(CLOCK_MONOTONIC, &now);
            HANDLE_ERROR(get_position(device, &position), "MMESSAHE");

            fprintf(file, "%i\t%.9lf\n", position, _get_elapsed_seconds(start_time, now));
            HANDLE_ERROR(get_motor_status(device, &motor_status), "MESSAGE");
        } while (motor_status != 0);
    }
    return SUCCESS;
}

// TODO error messagesj
Result move_cycle(Device device, const int amplitude, timespec *start_time, FILE *file) {
    clock_gettime(CLOCK_MONOTONIC, start_time);
    HANDLE_ERROR(move_stage(device, -amplitude), "MESSAGE");
    wait_for_motor_idle(device, *start_time, file);
    HANDLE_ERROR(move_stage(device, amplitude), "MESSAGE");
    wait_for_motor_idle(device, *start_time, file);
    return SUCCESS;
}
