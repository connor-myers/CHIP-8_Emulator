#ifndef MAIN_H
#define MAIN_H

/* Includes */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "exit.h"
#include "utility.h"

/* Constants */
#define MIN_ARGS            2           // Minimum number of args required for
                                        // program to run
#define ROM_FILE_EXTN       "ch8"       // The file extension for a CHIP-8 ROM 
#define DEFAULT_CLOCK_SPEED 500         // The default number of CPU 
                                        // instructions per second
#define DEFAULT_SCALER      25          // The default scaling of display


/* Typedefs */
typedef struct Settings
{
        bool debugMode;         // True iff user specified debug flag
        int clockSpeed;         // The number of CPU instructions executed per
                                                // second (default = 500Hz)
        uint8_t displayScale;   // The amount the display should be scaled by
                                                //(default = 25)
        const char *rom;        // The path of the ROM to be run
} Settings;

/* Functions */
void load_settings(Settings *settings, int numArgs, char **arguments);

#endif