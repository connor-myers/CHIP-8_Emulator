#ifndef ERRS_H
#define ERRS_H

#include <stdio.h>
#include <stdlib.h>

typedef enum Error {
    NORMAL = 0,
    BAD_ARGS = 1,
    BAD_ROM = 2,
    BAD_INSTRUCTION = 3,
    GRAPHICS_INIT_ERROR = 4,
    UNKNOWN_FONT_DATA = 5
} Error;

void err_msg(Error errCode);

#endif