#ifndef ERRS_H
#define ERRS_H

#include <stdio.h>
#include <stdlib.h>

typedef enum Error {
    NORMAL = 0,
    BAD_ARGS = 1,
    BAD_ROM = 2
} Error;

void err_msg(Error errCode);

#endif