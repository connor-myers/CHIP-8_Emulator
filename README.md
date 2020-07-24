# CHIP-8 Emulator


CHIP-8 is an interpreted programming language designed to run on CHIP-8 hardware. Unfortunately, real CHIP-8 hardware doesn't exist and, actually, never did. CHIP-8 programs were always intended to be run on virtual machines, i.e. an emulator, i.e. this project.

Below is a screenshot of my emulator running a CHIP-8 version of Pong.

![Screenshot of Pong](https://i.ibb.co/jvFvYLw/pong1.png)

Currently, all CHIP-8 features are implemented, including sound.

The emulator itself was written in C, using the SDL library for graphics and audio.

## Requirements to Run

-SDL2
-ncurses
-POSIX compliant system (I used getopt.h for args processing)

## How to Run
Simply clone the repo and make it. To run pong with no fancy settings, input the command
```
./chip8 roms/pong.ch8
```

However, the default clock-speed of chip-8 (500Hz) when running on modern machines proves to be insufficient for some programs. Furthermore, my default scaling might be too small
for your curved 35" 4k Korean gaming monitor. These values, along with the addition of a debugger, can be modified with additional flags.
### -d
Enables debugger, not sure why anyone other than me would use this.
Regardless, this lets you see an ASCII form of the display (I used this when SDL wasn't working) as well as the values of all the registers, timers and alike.

### -r?
Changes the refresh rate. By default this is 500Hz. For games like pong, a faster refresh rate is better. I like to use 800Hz, i.e. -r800. If you think you're hot stuff you can crank that up to 1000Hz, but you just might start losing to an "AI" competitor whose behaviour consists of a measly 4 bytes of code. Pathetic. (Game speed is directly tied to the "clock" speed, so 1000Hz results in quite a fast game of Pong).

### -s?
CHIP-8 uses a 64x32 display. This is obviously far too small for modern displays, so we need to scale the display up. If you don't specify a scaling, the program
will automatically scale it to x25. If this is too small or large for you, simply add -sx where x is a number bigger than 0. 

For example, my ideal pong arguments are:
```
./chip8 -d -r800 -s30 roms/pong.ch8
```

## Flicker
For certain technical reasons, all CHIP-8 programs flicker. It's not my emulator or your computer goofing, that's just what CHIP-8 programs do. There is probably
some crazy magic voodoo technique that can reduce this but that would hardly be in line with creating a pure CHIP-8 emulator (I also imagine it would be quite difficult to do).

## To-Do
- Make the debugger not hurt my eyes as much
- Add real-time speed changes
- Allow for breakpoints
- Rewinding time
- Reduce flickering

# References
These were the main resources I used for making the emulator
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.5
https://en.wikipedia.org/wiki/CHIP-8

