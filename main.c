#include "main.h"

int main(int argc, char **argv)
{
    if (argc != NUM_ARGS) {
        err_msg(BAD_ARGS);
    }

    Stack stack;
    stack_init(&stack, sizeof(short));

    short one = 1;
    short two = 69;
    short three = 3;

    stack_push(&stack, (void *) &one);
    stack_push(&stack, (void *) &two);
    stack_push(&stack, (void *) &three);

    short *first;
    short *second;
    short *third;

    first = (short*) stack_pop(&stack); 
    second = (short*) stack_pop(&stack); 
    third = (short*) stack_pop(&stack); 

    printf("%d, %d, %d\n", *first, *second, *third);


    return 0;
}