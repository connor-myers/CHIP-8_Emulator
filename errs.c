#include "errs.h"

/*
    summary:    Prints corresponding error message to STDERR and terminated program with status errCode

    errCode:    The code to exit the program with, and to display the corresponding message for

*/
void err_msg(Error errCode)
{
    char *msg;
    switch(errCode)
    {
        case NORMAL:
            exit(errCode); // don't need to print message, exit straight away
            break;
        case BAD_ARGS:
            msg = "Invalid number of arguments";
            break;
        case BAD_ROM:
            msg = "Bad ROM File";
            break;    
        default:
            msg = "Unknown Error Code";
    }    
    fprintf(stderr, "%s\n", msg);
    fflush(stderr);
    exit(errCode);
}