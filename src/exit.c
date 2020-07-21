#include "headers/exit.h"

/*
        summary:        Exits the program with specified exit code, as well as printing
                                the corresponding message to STDERR

        code:                The exit code to exit the program with and print the
                                corresponding message for
*/
void exit_with_msg(ExitCode code)
{
        const char *exit_msgs[2] = {
                                                        "Program exited normally",
                                                        "Program run with invalid number of arguments"
                                                     };
        if (code == 0)
        {
                fprintf(stderr, "%s\n", exit_msgs[code]);
        } else {
                fprintf(stderr, "Error (%d): %s\n", code, exit_msgs[code]);
        }                                          
        fflush(stderr);
        exit(code);
}