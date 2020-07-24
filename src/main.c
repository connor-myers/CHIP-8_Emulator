#include "headers/main.h"

int main(int argc, char **argv)
{

        // Make sure SDL can handle audio and video
        SDL_Init(SDL_INIT_EVERYTHING);

        // set up signal handler
        setup_signal_handlers(); 

        if (argc < MIN_ARGS)
        {
                exit_with_msg(BAD_NUM_ARGS);                           
        }     

        // extract and parse user args
        Settings userSettings;
        load_settings(&userSettings, argc, argv);   

        // initialises emulator, display and sound
        CHIP8 chip8;
        init_CHIP8(&chip8, &userSettings);

        SDL_Window *window;
        init_display(&window, &userSettings);

        init_sound();

        // load ROM into memory
        load_rom(&chip8, userSettings.rom);

        // initialise debugger (if specified in flags)
        if (userSettings.debugMode)
        {
                init_debugger(&chip8);
        }

        for (;;)
        {
                process_input(&chip8);

                // update timers
                update_timers(&chip8);
                
                time_t currentTime = GET_TIME_IN_MS;
                if (currentTime - chip8.lastCycleTime
                        > 1000 / userSettings.clockSpeed)
                {
                        // emulate cycle
                        run_cpu_cycle(&chip8);

                        // update graphics
                        if (chip8.drawFlag)
                        {
                                update_display(window, chip8.display,
                                        userSettings.displayScale);
                                chip8.drawFlag = 0;
                        }
                        
                        // update debugger
                        if (userSettings.debugMode)
                        {
                                update_debugger(&chip8);
                        }

                        // play sound
                        if (chip8.soundTimer > 0) 
                        {
                                play_audio();
                        } else {
                                pause_audio();
                        }

                        chip8.lastCycleTime = currentTime;
                }
        }
}

/*
        summary:        Loads user settings from program arguments

        settings:       Pointer to empty settings block
        numArgs:        The number of arguments (argc - 1)
        arguments:      The arguments into the program
                        (not including program name)
*/
void load_settings(Settings *settings, int numArgs, char **arguments)
{
        settings->debugMode = false;
        settings->clockSpeed = DEFAULT_CLOCK_SPEED;
        settings->displayScale = DEFAULT_SCALER;

        int opt;
        while ((opt = getopt(numArgs, arguments, "r:s:d")) != -1) 
        {
                switch (opt) 
                {
                        case 'r':
                        {
                                settings->clockSpeed = atoi(optarg);
                                if (settings->clockSpeed <= 0)
                                {
                                        exit_with_msg(BAD_REFRESH_FLAG);
                                }        
                        }
                        break;
                        case 's':
                        {
                                settings->displayScale = atoi(optarg);
                                if (settings->clockSpeed <= 0)
                                {
                                        exit_with_msg(BAD_SCALE_FLAG);
                                }  
                        }
                        break;
                        case 'd':
                        {
                                settings->debugMode = true;
                        }
                        break;
                }
        }

        settings->rom = arguments[optind];
        char *fileExtension = get_file_extension(settings->rom);
        if (fileExtension == NULL || strcmp(fileExtension, ROM_FILE_EXTN) != 0)
        {
                exit_with_msg(BAD_ROM);
        }
}

/*
        summary:        Sets up signal handler for program
*/
void setup_signal_handlers(void)
{
        struct sigaction sa;
        sa.sa_handler = handle_signals;   
        sa.sa_flags = SA_RESTART;
        sigaction(SIGTERM, &sa, 0);
        sigaction(SIGINT, &sa, 0);
        sigaction(SIGQUIT, &sa, 0);
}

/*
        summary:        handle signals

        signal:         The signal to handle
*/
void handle_signals(int signal)
{
        // turn off ncurses 
        endwin();    
        // free audio resources
        release_audio_resources();
        fprintf(stderr, "Exiting due to receiving %s signal\n",
                        strsignal(signal));
        fflush(stderr);
        exit(signal);     
}

/*
        summary:        Frees any heap allocated resources
                        And terminates program cleanly
*/
void clean_and_exit()
{
        endwin();
        release_audio_resources();
        exit(0);
}