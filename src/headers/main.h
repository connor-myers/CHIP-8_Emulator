#ifndef MAIN_H
#define MAIN_H

/* Includes */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "exit.h"

/* Constants */
#define MIN_ARGS        2                  // Minimum number of args required for program to run

/* Typedefs */
typedef struct Settings
{
        bool debugMode;                         // True iff user specified debug flag
        uint8_t clockSpeed;                     // The number of CPU instructions executed per second 
                                                             // (default = 500Hz)                    
        uint8_t displayScale;                   // The amount the display should be scaled by (default = 25)
        const char *rom;                          // The path of the ROM to be run
} Settings;

/* Functions */
void load_settings(Settings *settings, int numArgs, char **arguments);

#endif