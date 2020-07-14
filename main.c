#include "main.h"

int main(int argc, char **argv)
{
    if (argc != NUM_ARGS) {
        err_msg(BAD_ARGS);
    }

    CPU cpu;
    cpu_init(&cpu);

    init_display();

    // loading ROM
    FILE *rom = fopen(argv[1], "r");
    if (rom == NULL)
    {
        err_msg(BAD_ROM);
    }

    load_rom(&cpu, rom);

    for(;;)
    {
        process_cycle(&cpu);

        // update display

        // set keys                
    }

    return 0;
}