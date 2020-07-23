#ifndef MAIN_H
#define MAIN_H

/* Includes */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
#include "chip8.h"
#include "exit.h"
#include "utility.h"
#include "debug.h"
#include "settings.h"
#include "input.h"

/* Constants */
#define MIN_ARGS            2           // Minimum number of args required for
                                        // program to run
#define ROM_FILE_EXTN       "ch8"       // The file extension for a CHIP-8 ROM 
#define DEFAULT_CLOCK_SPEED 500         // The default number of CPU 
                                        // instructions per second
#define DEFAULT_SCALER      25          // The default scaling of display


/* Typedefs */


/* Functions */
void load_settings(Settings *settings, int numArgs, char **arguments);
void setup_signal_handlers(void);
void handle_signals(int signal);

#endif