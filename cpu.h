#ifndef CPU_H
#define CPU_H

#include <string.h>
#include "stack.h"

#define MEMORY_SIZE 4096
#define NUM_REGISTERS 16

typedef struct CPU {
    unsigned int memory[MEMORY_SIZE];
    unsigned int registers[NUM_REGISTERS];
    Stack *stack;    
} CPU;

void cpu_init(CPU *cpu);

#endif 