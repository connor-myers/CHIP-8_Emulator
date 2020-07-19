#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stack.h"
#include "errs.h"
#include "display.h"

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define NUM_KEYS 0xF
#define PROGRAM_START 0x200         // the address program execution begins at
#define COLLISION 1
#define NO_COLLISION 0
#define PERIOD 16.6666666667        // period in ms

typedef unsigned short Opcode;


typedef struct CPU {
    uint8_t memory[MEMORY_SIZE];                                   // CHIP-8 Memory
    uint8_t registers[NUM_REGISTERS];                              // CHIP-8 Registers
    uint8_t keyboard[NUM_KEYS];
    Stack stack;                                                   // program stack
    int16_t pc;                                                    // program counter
    uint8_t display[SCREEN_HEIGHT][SCREEN_WIDTH];                // the graphical display
    uint16_t i;                                                    // I register
    uint8_t drawFlag;                                              // Draw flag
    time_t delayTimer;
    time_t soundTimer;
    time_t lastCycleTime;                                           // Time of last CPU cycle


} CPU;

void cpu_init(CPU *cpu);
void process_cycle(CPU *cpu);
Opcode get_next_instruction(CPU *cpu);
void update_timers(CPU *cpu);
void perform_instruction(CPU *cpu, Opcode instruction);
uint8_t get_font_address(uint8_t value);
void load_font_data(CPU *cpu);
void load_rom(CPU *cpu, FILE *file);

#endif 