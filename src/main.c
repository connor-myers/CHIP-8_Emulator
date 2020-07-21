#include "headers/main.h"

int main(int argc, char **argv)
{
        if (argc < MIN_ARGS)
        {
                exit_with_msg(BAD_NUM_ARGS);                           
        }     

        Settings userSettings;
        load_settings(&userSettings, argc - 1, argv + 1);        
}

/*
        summary:        Loads user settings from program arguments

        settings:           Pointer to empty settings block
        numArgs:        The number of arguments (argc - 1)
        arguments:      The arguments into the program (not including program name)
*/
void load_settings(Settings *settings, int numArgs, char **arguments)
{
                
}