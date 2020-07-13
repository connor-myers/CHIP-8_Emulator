#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#define INITIAL_CAPACITY 10     // the initial capacity of a stack
#define GROWTH_RATE 2           // how much the stack grows by when it reaches capacity

typedef struct Stack {
    size_t size;                // the number of entries in the stack
    size_t capacity;            // the max number of entries that can fit in this stack
    size_t entrySize;           // the size of a single entry in the stack
    void **entries;             // the entries in the stack
} Stack;

void stack_init(Stack *stack, size_t entrySize);
void stack_push(Stack *stack, void *entry);
void *stack_pop(Stack *stack);

#endif
