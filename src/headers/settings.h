#ifndef SETTINGS_H
#define SETTINGS_H

/** Includes **/
#include <stdbool.h>
#include <stdint.h>

typedef struct Settings
{
        bool debugMode;         // True iff user specified debug flag
        int clockSpeed;         // The number of CPU instructions executed per
                                                // second (default = 500Hz)
        uint8_t displayScale;   // The amount the display should be scaled by
                                                //(default = 25)
        const char *rom;        // The path of the ROM to be run
} Settings;

#endif;