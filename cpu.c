#include "cpu.h"

/*
    summary:    Initialises a new CPU

    cpu:        Pointer to an empty CPU struct
*/
void cpu_init(CPU *cpu)
{
    memset(cpu->memory, 0, MEMORY_SIZE * sizeof(unsigned int));
    memset(cpu->registers, 0, NUM_REGISTERS * sizeof(unsigned int));
    stack_init(cpu->stack);
}

