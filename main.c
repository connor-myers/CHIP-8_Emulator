#include "main.h"

int main(int argc, char **argv)
{
    if (argc != NUM_ARGS) {
        err_msg(BAD_ARGS);
    }

    CPU cpu;
    cpu_init(&cpu);

    // SDL_Window *window;
    // //init_display(&window);

    // //update_display(window, cpu.display);

    // // loading ROM
    // FILE *rom = fopen(argv[1], "r");
    // if (rom == NULL)
    // {
    //     err_msg(BAD_ROM);
    // }

    // load_rom(&cpu, rom);


    //SDL_Delay(5000);

    //SDL_DestroyWindow( window );

    //Quit SDL subsystems
    // SDL_Quit();

    for(;;)
    {
        //process_cycle(&cpu);

        // update display
        // update_display(window, cpu.display);

        // set keys    

        // timers    
        update_timers(&cpu);
    }

    return 0;
}