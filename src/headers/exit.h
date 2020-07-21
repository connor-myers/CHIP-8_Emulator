#ifndef ERROR_H
#define ERROR_H

/* Includes */
#include <stdio.h>

/* Constants */

/* Typedefs */
typedef enum ExitCode
{
        NORMAL,                 // Program exited normally
        BAD_NUM_ARGS,           // Program started with invalid number of args
        BAD_REFRESH_FLAG,       // Bad refresh rate provided in args
        BAD_SCALE_FLAG,          // Bad display scaler provided in args
        BAD_ROM                 // Bad rom provided
} ExitCode;

/* Functions */
void exit_with_msg(ExitCode code);

#endif