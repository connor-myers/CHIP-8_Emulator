#ifndef DEBUG_H
#define DEBUG_H

/** Includes **/
#include <curses.h>
#include "chip8.h"

/** Definitions **/

/** Functions  **/
void init_debugger(CHIP8* chip8);
void update_debugger(CHIP8* chip8);
void draw_display_window(CHIP8* chip8);
void draw_registers_window(CHIP8* chip8);
void draw_stack_window(CHIP8* chip8);
void draw_keyboard_window(CHIP8* chip8);
void draw_rom_window(CHIP8* chip8);

#endif
