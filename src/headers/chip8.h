#ifndef CHIP8_H
#define CHIP8_H

/** Includes **/
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "graphics.h"
#include "settings.h"
#include "exit.h"

/** Constants **/

#define MEMORY_SIZE     0x1000          // CHIP-8 has 0x1000 (4096) 8-bit
                                        // memory cells
#define NUM_REGISTERS   0x10            // CHIP-8 has 0x10 (16) registers
#define NUM_KEYS        0xF             // CHIP-8 supports 0xF (15) keys
#define STACK_SIZE      0x10            // The CHIP-8 stack can hold 0x10 (16)
                                        // addresses              
#define PROGRAM_START   0x200           // The memory address where program
                                        // execution begins at

/** Typedefs **/

typedef struct CHIP8 {
        Settings *userSettings;                         // User settings
        uint8_t memory[MEMORY_SIZE];                    // CHIP-8 Memory
        uint8_t registers[NUM_REGISTERS];               // CHIP-8 Registers
        uint8_t keyboard[NUM_KEYS];                     // Keyboard values
        uint16_t stack[STACK_SIZE];                     // Stack
        uint8_t sp;                                     // Stack pointer
        int16_t pc;                                     // program counter
        uint8_t display[SCREEN_HEIGHT][SCREEN_WIDTH];   // the graphical display
        uint16_t i;                                     // I register
        uint8_t drawFlag;                               // Draw flag
        time_t delayTimer;                              // Delay timer  
        time_t soundTimer;                              // Sound timer
} CHIP8;


/** Functions **/

void init_CHIP8(CHIP8 *chip8, Settings *userSettings);
void load_rom(CHIP8 *chip8, char *rom);
void load_font_data(CHIP8 *chip8);

#endif