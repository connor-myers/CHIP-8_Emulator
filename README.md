# CHIP-8 Emulator


CHIP-8 is an interpreted programming language designed in the 70s to make writing computer games easier for certain computers. CHIP-8 programs run on a CHIP-8 virtual machine, which is what this project is. CHIP-8 is typically used as an introduction to emulation due to it's small instruction set and relatively simple implementation.

Currently, all CHIP-8 features are implemented, including sound.

The emulator itself was written in C, using the SDL2 library for graphics and audio.

Below is a screenshot of my emulator running Pong.

![Screenshot of Pong](https://i.ibb.co/jvFvYLw/pong1.png)

## Requirements to Run

-SDL2

-ncurses

-POSIX compliant OS

## How to Run
Simply clone the repo and make it. To run pong with no fancy settings, input the command
```
./chip8 roms/pong.ch8
```

## Flags

### -d
Enables the debugger.

### -s[scale_factor] 
This scales the default 64 x 32 display. I generally use 25x scaling.

### -f[refresh_rate]
CHIP-8 by default has a clock speed of 500Hz. However, when running on modern hardware and for some games, it can be better to run some games at a faster rate.

## Example

For example, my ideal arguments to run pong.
```
./chip8 -d -r800 -s30 roms/pong.ch8
```

# References
These were the main resources I used for making the emulator
- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.5
- https://en.wikipedia.org/wiki/CHIP-8

