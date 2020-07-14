#include "stack.h"


void stack_init(Stack *stack)
{
    stack->capacity = STACK_CAPACITY;
    stack->size = 0;
    memset(stack->entries, 0, STACK_CAPACITY * sizeof(unsigned short));
}

void stack_push(Stack *stack, unsigned short entry)
{
    stack->entries[stack->size] = entry;
    stack->size++;
}

unsigned short stack_pop(Stack *stack)
{
    return stack->entries[stack->size];
    stack->size--;
}