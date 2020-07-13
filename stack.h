#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define STACK_CAPACITY 16

typedef struct Stack {
    size_t capacity;            // the max size of the stack
    size_t size;                // the number of entries in the stack
    unsigned short *entries;    // the entires in the stack. Chip-8 stack uses 2 byte Program Counters, hence short
} Stack;

void stack_init(Stack *stack);
void stack_push(Stack *stack, unsigned short entry);
unsigned short stack_pop(Stack *stack);

#endif
