#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "../cpu.h"
#include <stdbool.h>

typedef enum Result {
    FAIL = 0,
    PASS = 1
} Result;

void print_error(char *string);
void print_good(char *string);

// tests
Result test_00E0(CPU *cpu);
Result test_00EE(CPU *cpu);
Result test_1nnn(CPU *cpu);

// utility
void print_display(CPU* cpu);

#endif