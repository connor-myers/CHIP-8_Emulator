#include "stack.h"

/*
    summary:    Initialises a new stack

    stack:      Pointer to the stack to be initialised

    entrySize:  Size of a single entry (for CHIP-8, this will be a short; 2 bytes)
*/
void stack_init(Stack *stack, size_t entrySize)
{
    stack->capacity = INITIAL_CAPACITY;
    stack->size = 0;
    stack->entries = calloc(stack->capacity, entrySize);
    stack->entrySize = entrySize;
}

/*
    summary:    Pushes a new element onto the stack. If capacity is reached, will allocate mote space

    stack:      Pointer to the stack the entry will be added to

    entry:      The entry cast as a void*
*/
void stack_push(Stack *stack, void *entry)
{
    // making room in the stack if stack is full
    if (stack->size == stack->capacity)
    {
        stack->capacity *= GROWTH_RATE;
        stack->entries = realloc(stack->entries, stack->entrySize * stack->capacity);
    }

    stack->entries[stack->size] = entry;
    stack->size++;
}

/*
    summary:    Pops an element from the stack.

    stack:      Pointer to the stack that the top entry will be popped from
*/
void *stack_pop(Stack *stack)
{
    return stack->entries[--stack->size];
}

