#include "main.h"

int main(int argc, char **argv)
{
    if (argc != NUM_ARGS) {
        err_msg(BAD_ARGS);
    }

    CPU cpu;
    cpu_init(&cpu);    

    return 0;
}