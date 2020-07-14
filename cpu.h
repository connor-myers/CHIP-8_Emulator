#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "stack.h"
#include "errs.h"

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16
#define PROGRAM_START 0x200         // the address program execution begins at

typedef unsigned short Opcode;

typedef struct CPU {
    unsigned int memory[MEMORY_SIZE];
    unsigned int registers[NUM_REGISTERS];
    Stack stack;
    int16_t pc;                                 // program counter

} CPU;

void cpu_init(CPU *cpu);
void process_cycle(CPU *cpu);
Opcode get_next_instruction(CPU *cpu);
void perform_instruction(CPU *cpu, Opcode instruction);
void load_font_data(CPU *cpu);
void load_rom(CPU *cpu, FILE *file);

#endif 