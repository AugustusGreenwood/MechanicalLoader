#ifndef RESULT_H
#define RESULT_H

#include <stdio.h>

/*
 * This specifies whether a complete report of all errors experience should be reported
 * or just user chosen ones
 */
#ifdef DEBUGLOG
#define LOG_ERROR(result, msg)                                                           \
    do {                                                                                 \
        printf("Error occured, information is:\n"                                        \
               "Code:      %i\n"                                                         \
               "File:      %s\n"                                                         \
               "Line:      %i\n"                                                         \
               "Function:  %s\n"                                                         \
               "Message:   %s\n",                                                        \
               result, __FILE__, __LINE__, __FUNCTION__, msg);                           \
    } while (0)
#else
#define LOG_ERROR(result, msg)                                                           \
    do {                                                                                 \
    } while (0)
#endif

/*
 * These help me handle errors. I wanted a way to quickly for on expression failure
 * return result and log error
 */
#define HANDLE_ERROR(expr, msg)                                                          \
    do {                                                                                 \
        Result result = (expr);                                                          \
        if (result != SUCCESS) {                                                         \
            LOG_ERROR(result, msg);                                                      \
            return result;                                                               \
        }                                                                                \
    } while (0)

/*
 * This is helpful in a few circumstances, some errors aren't a big deal or expected
 * for some operations, just wanted an easy way to ignore them. Currently only for a
 * single error
 */
#define HANDLE_ERROR_UNLESS(error, expr, msg)                                            \
    do {                                                                                 \
        Result result = (expr);                                                          \
        if ((result != SUCCESS) && (result != error)) {                                  \
            LOG_ERROR(result, msg);                                                      \
            return result;                                                               \
        }                                                                                \
    } while (0)

#define HANDLE_ERROR_DONT_RETURN(expr, msg)                                              \
    do {                                                                                 \
        Result result = (expr);                                                          \
        if (result != SUCCESS) {                                                         \
            LOG_ERROR(result, msg);                                                      \
        }                                                                                \
    } while (0)

// These are all just libusb errors with just a few of mine
typedef enum Result {
    ARCUS_ERROR = 1,
    INPUT_ERROR = 2,

    SUCCESS = 0,
    IO_ERROR = -1,
    INVALID_PARAM_ERROR = -2,
    ACCESS_ERROR = -3,
    NO_DEVICE_ERROR = -4,
    NOT_FOUND_ERROR = -5,
    BUSY_ERROR = -6,
    TIMEOUT_ERROR = -7,
    OVERFLOW_ERROR = -8,
    PIPE_ERROR = -9,
    INTERRUPTED_ERROR = -10,
    NO_MEM_ERROR = -11,
    NOT_SUPPORTED_ERROR = -12,
    OTHER_ERROR = -99
} Result;

#endif
