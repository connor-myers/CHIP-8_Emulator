#ifndef ERROR_H
#define ERROR_H

/* Includes */
#include <stdio.h>

/* Constants */

/* Typedefs */
typedef enum ExitCode
{
        NORMAL,                                 // Program exited normally
        BAD_NUM_ARGS,                  // Program started with invalid number of args
} ExitCode;

/* Functions */
void exit_with_msg(ExitCode code);

#endif