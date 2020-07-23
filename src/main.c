#include "headers/main.h"

int main(int argc, char **argv)
{
        if (argc < MIN_ARGS)
        {
                exit_with_msg(BAD_NUM_ARGS);                           
        }     

        // extract and parse user args
        Settings userSettings;
        load_settings(&userSettings, argc - 1, argv + 1);    

        CHIP8 chip8;
        init_CHIP8(&chip8, &userSettings);

        // load ROM into memory
        load_rom(&chip8, userSettings.rom);

        // initialise debugger (if specified in flags)
        if (userSettings.debugMode)
        {
                init_debugger(&chip8);
        }

        for (;;)
        {
                time_t currentTime = GET_TIME_IN_MS;
                if (currentTime - chip8.lastCycleTime
                        > 1000 / userSettings.clockSpeed)
                {
                        // emulate cycle
                        run_cpu_cycle(&chip8);

                        // update graphics
                        
                        // update timers
                        update_timers(&chip8);

                        // update debugger
                        if (userSettings.debugMode)
                        {
                                update_debugger(&chip8);
                        }
                        chip8.lastCycleTime = currentTime;
                }
        }

        if (userSettings.debugMode)
        {
                endwin();
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
        settings->rom = arguments[numArgs - 1];

        char *fileExtension = get_file_extension(settings->rom);
        if (fileExtension == NULL || strcmp(fileExtension, ROM_FILE_EXTN) != 0)
        {
                exit_with_msg(BAD_ROM);
        }

        for (int i = 0; i < numArgs - 1; i++)
        {
                if (strcmp(arguments[i], "-d") == 0)
                {
                        settings->debugMode = true;
                }
                if (arguments[i][0] == '-' && arguments[i][1] == 'r')
                {
                        StringConErr error = GOOD;
                        settings->clockSpeed = 
                                        string_to_int(arguments[i] + 2, &error);
                        if (error || settings->clockSpeed <= 0)
                        {
                                exit_with_msg(BAD_REFRESH_FLAG);                           
                        } 
                }
                if (arguments[i][0] == '-' && arguments[i][1] == 's')
                {
                        StringConErr error = GOOD;
                        settings->displayScale = 
                                        string_to_int(arguments[i] + 2, &error);
                        if (error || settings->displayScale <= 0)
                        {
                                exit_with_msg(BAD_REFRESH_FLAG);                           
                        } 
                }
        }    
}