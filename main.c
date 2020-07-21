#include "main.h"

int main(int argc, char **argv)
{
    if (argc != NUM_ARGS) {
        err_msg(BAD_ARGS);
    }

    CPU cpu;
    cpu_init(&cpu);

    SDL_Window *window;
    init_display(&window);

    update_display(window, cpu.display);

    // loading ROM
    FILE *rom = fopen(argv[1], "r");
    if (rom == NULL)
    {
        err_msg(BAD_ROM);
    }

    load_rom(&cpu, rom);


    //SDL_Delay(5000);

    //SDL_DestroyWindow( window );

    //Quit SDL subsystems
    // SDL_Quit();

    cpu.lastCycleTime = clock() * 1000 / CLOCKS_PER_SEC;

    for(;;)
    {
        process_input(&cpu);
        time_t currentTime = clock() * 1000 / CLOCKS_PER_SEC;
        if ((currentTime - cpu.lastCycleTime) > DELAY)
        {
            process_cycle(&cpu);
            // update display
            if (cpu.drawFlag)
            {
                update_display(window, cpu.display);
                cpu.drawFlag = 0;
            }
            // timers    
            update_timers(&cpu);

            cpu.lastCycleTime = currentTime;
        }
    }

    return 0;
}

void process_input(CPU *cpu)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
                    exit(0); // close the game
				} break;

				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
                            exit(0); // close the game
						} break;

						case SDLK_x:
						{
							cpu->keyboard[0] = 1;
						} break;

						case SDLK_1:
						{
							cpu->keyboard[1] = 1;
						} break;

						case SDLK_2:
						{
							cpu->keyboard[2] = 1;
						} break;

						case SDLK_3:
						{
							cpu->keyboard[3] = 1;
						} break;

						case SDLK_q:
						{
							cpu->keyboard[4] = 1;
						} break;

						case SDLK_w:
						{
							cpu->keyboard[5] = 1;
						} break;

						case SDLK_e:
						{
							cpu->keyboard[6] = 1;
						} break;

						case SDLK_a:
						{
							cpu->keyboard[7] = 1;
						} break;

						case SDLK_s:
						{
							cpu->keyboard[8] = 1;
						} break;

						case SDLK_d:
						{
							cpu->keyboard[9] = 1;
						} break;

						case SDLK_z:
						{
							cpu->keyboard[0xA] = 1;
						} break;

						case SDLK_c:
						{
							cpu->keyboard[0xB] = 1;
						} break;

						case SDLK_4:
						{
							cpu->keyboard[0xC] = 1;
						} break;

						case SDLK_r:
						{
							cpu->keyboard[0xD] = 1;
						} break;

						case SDLK_f:
						{
							cpu->keyboard[0xE] = 1;
						} break;

						case SDLK_v:
						{
							cpu->keyboard[0xF] = 1;
						} break;
					}
				} break;

				case SDL_KEYUP:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_x:
						{
							cpu->keyboard[0] = 0;
						} break;

						case SDLK_1:
						{
							cpu->keyboard[1] = 0;
						} break;

						case SDLK_2:
						{
							cpu->keyboard[2] = 0;
						} break;

						case SDLK_3:
						{
							cpu->keyboard[3] = 0;
						} break;

						case SDLK_q:
						{
							cpu->keyboard[4] = 0;
						} break;

						case SDLK_w:
						{
							cpu->keyboard[5] = 0;
						} break;

						case SDLK_e:
						{
							cpu->keyboard[6] = 0;
						} break;

						case SDLK_a:
						{
							cpu->keyboard[7] = 0;
						} break;

						case SDLK_s:
						{
							cpu->keyboard[8] = 0;
						} break;

						case SDLK_d:
						{
							cpu->keyboard[9] = 0;
						} break;

						case SDLK_z:
						{
							cpu->keyboard[0xA] = 0;
						} break;

						case SDLK_c:
						{
							cpu->keyboard[0xB] = 0;
						} break;

						case SDLK_4:
						{
							cpu->keyboard[0xC] = 0;
						} break;

						case SDLK_r:
						{
							cpu->keyboard[0xD] = 0;
						} break;

						case SDLK_f:
						{
							cpu->keyboard[0xE] = 0;
						} break;

						case SDLK_v:
						{
							cpu->keyboard[0xF] = 0;
						} break;
					}
				}   break;
			}
		}
}