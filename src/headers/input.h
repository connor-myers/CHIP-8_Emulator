#ifndef INPUT_H
#define INPUT_H

/** Includes **/

#include <SDL2/SDL.h>
#include <curses.h>
#include "chip8.h"

/** Functions **/

void process_input(CHIP8 *chip8);

#endif