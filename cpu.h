#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "errs.h"
#include "display.h"

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define PROGRAM_START 0x200         // the address program execution begins at
#define COLLISION 1
#define NO_COLLISION 0

typedef unsigned short Opcode;


typedef struct CPU {
    uint8_t memory[MEMORY_SIZE];                                   // CHIP-8 Memory
    uint8_t registers[NUM_REGISTERS];                              // CHIP-8 Registers
    Stack stack;                                                   // program stack
    int16_t pc;                                                    // program counter
    uint8_t display[SCREEN_HEIGHT][SCREEN_WIDTH];                // the graphical display
    uint16_t i;                                                    // I register
    uint8_t drawFlag;                                              // Draw flag
} CPU;

void cpu_init(CPU *cpu);
void process_cycle(CPU *cpu);
Opcode get_next_instruction(CPU *cpu);
void perform_instruction(CPU *cpu, Opcode instruction);
void load_font_data(CPU *cpu);
void load_rom(CPU *cpu, FILE *file);

#endif 