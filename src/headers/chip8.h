#ifndef CHIP8_H
#define CHIP8_H

/** Includes **/
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "graphics.h"
#include "settings.h"
#include "utility.h"
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
#define TIMER_PERIOD    1000  * 1/60    // Period for the 60Hz timers in ms                                      

/** Macros **/
#define NTH_HEX_DIGIT(X, N) ((X) >> ((N) * 4)) & 0xF
#define GET_TIME_IN_MS clock() * 1000 / CLOCKS_PER_SEC

/** Typedefs **/

typedef struct CHIP8 {
        Settings *userSettings;                         // User settings
        uint8_t memory[MEMORY_SIZE];                    // CHIP-8 Memory
        uint8_t registers[NUM_REGISTERS];               // CHIP-8 Registers
        uint8_t keyboard[NUM_KEYS];                     // Keyboard values
        uint16_t stack[STACK_SIZE];                     // Stack
        uint8_t sp;                                     // Stack pointer
        uint16_t pc;                                     // program counter
        uint8_t display[SCREEN_HEIGHT][SCREEN_WIDTH];   // the graphical display
        uint16_t i;                                     // I register
        uint8_t drawFlag;                               // Draw flag
        time_t delayTimer;                              // Delay timer  
        time_t soundTimer;                              // Sound timer
        time_t lastCycleTime;                           // Time of last cycle     
        time_t lastTimerUpdate;                         // When timers were last updated
} CHIP8;

typedef uint16_t Opcode;

/** Functions **/

void init_CHIP8(CHIP8 *chip8, Settings *userSettings);
void load_rom(CHIP8 *chip8, char *rom);
void update_timers(CHIP8 *chip8);
void run_cpu_cycle(CHIP8 *chip8);
void get_next_instruction(CHIP8 *chip8, Opcode *instruction);
void execute_instruction(CHIP8 *chip8, Opcode instruction);
void load_font_data(CHIP8 *chip8);

#endif