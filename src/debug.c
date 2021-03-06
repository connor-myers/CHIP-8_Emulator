#include "headers/debug.h"

WINDOW* romWindow;
WINDOW* specRegWindow;
WINDOW* displayWindow;
WINDOW* registersWindow;
WINDOW* stackWindow;
WINDOW* keyboardWindow;

void init_debugger(CHIP8* chip8)
{
        // initialising ncurses window
        initscr();
        cbreak();
        noecho();
        start_color();

        // initialising windows
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);

        romWindow = newwin(0.9 * yMax, xMax / 2, 0, xMax / 2);
        specRegWindow = newwin(0.1 * yMax, xMax / 2, 0.9 * yMax, xMax / 2);
        displayWindow = newwin(0.7 * yMax, xMax / 2, 0, 0);
        registersWindow = newwin(0.1 * yMax, xMax / 2, 0.7 * yMax, 0);
        stackWindow = newwin(0.1 * yMax, xMax / 2, 0.8 * yMax, 0);
        keyboardWindow = newwin(0.1 * yMax, xMax / 2, 0.9 * yMax, 0);
        refresh();

        // draw boxes 

        wborder(romWindow, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(romWindow);

        wborder(specRegWindow, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(specRegWindow);

        wborder(displayWindow, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(displayWindow);

        wborder(registersWindow, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(registersWindow);

        wborder(stackWindow, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(stackWindow);

        wborder(keyboardWindow, '#', '#', '#', '#', '#', '#', '#', '#');
        wrefresh(keyboardWindow);
}

void update_debugger(CHIP8* chip8)
{
        draw_display_window(chip8);    
        draw_registers_window(chip8);    
        draw_stack_window(chip8);
        draw_keyboard_window(chip8);
        draw_rom_window(chip8);
        draw_spec_window(chip8);
}

void draw_display_window(CHIP8* chip8)
{
        mvwprintw(displayWindow, 1, 2, "Display Memory");
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
                for (int j = 0; j < SCREEN_WIDTH; j++)
                {
                        mvwprintw(displayWindow, 3 + i, 2 + j, "%d",
                                        chip8->display[i][j]);
                }
        }
        wrefresh(displayWindow);
}

void draw_registers_window(CHIP8* chip8)
{
        mvwprintw(registersWindow, 1, 2, "Registers Values");
        for (int i = 0; i < NUM_REGISTERS; i++)
        {
        mvwprintw(registersWindow, 3, 2 + (i * 4), "Vx%x",
                        i);
        mvwprintw(registersWindow, 4, 2 + (i * 4), "[%x]",
                        chip8->registers[i]);
        }
        wrefresh(registersWindow);
}

void draw_stack_window(CHIP8* chip8)
{ 
        mvwprintw(stackWindow, 1, 2, "Stack Values");
        for (int i = 0; i < STACK_SIZE; i++)
        {
                if (i == chip8->sp)
                {
                        wattron(stackWindow, A_STANDOUT);                
                }   
                mvwprintw(stackWindow, 3, 3 + (i * 4), "%x",
                                i);
                wattroff(stackWindow, A_STANDOUT);
                mvwprintw(stackWindow, 4, 2 + (i * 4), "[%x]",
                                chip8->stack[i]);
        }

        wrefresh(stackWindow);
}

void draw_keyboard_window(CHIP8* chip8)
{
        mvwprintw(keyboardWindow, 1, 2, "Keyboard Values");
        for (int i = 0; i < NUM_KEYS; i++)
        {
        mvwprintw(keyboardWindow, 3, 3 + (i * 4), "%x",
                        i);
        mvwprintw(keyboardWindow, 4, 2 + (i * 4), "[%x]",
                        chip8->keyboard[i]);
        
        }
        wrefresh(keyboardWindow);
}

void draw_rom_window(CHIP8* chip8)
{
        mvwprintw(romWindow, 1, 2, "Memory");
        for (int i = 0; i < 0x64; i++)
        {
                for (int j = 0; j < 0x64; j++)
                {
                        mvwprintw(romWindow, 2 + i, 2 + j, "%02x",
                        chip8->memory[i * j]);
                }                
        }

        wrefresh(romWindow);        
}

void draw_spec_window(CHIP8* chip8)
{
        mvwprintw(specRegWindow, 1, 2, "Special Values");
        mvwprintw(specRegWindow, 3, 2, "sp=%02x pc=%04x dt=%04x st=%04x i=%04x",
                chip8->sp, chip8->pc, chip8->delayTimer, chip8->soundTimer,
                chip8->i);     
        wrefresh(specRegWindow);   
}