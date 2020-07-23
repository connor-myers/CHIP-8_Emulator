CC = gcc
OPTS =	-Wall -lncurses -pedantic -g -w -std=gnu99
SRC_OBJ = src/main.c src/chip8.c src/graphics.c src/input.c src/sound.c src/timer.c src/debug.c src/exit.c src/utility.c
TST_OBJ = test/main.c

all:	chip8 chip8_test clean

%.o: %.c
	$(CC) -c -o $@ $< $(OPTS)

chip8: $(SRC_OBJ)
	$(CC) -o $@ $^ $(OPTS) -lSDL2

chip8_test: $(TST_OBJ)
	$(CC) -o $@ $^ $(OPTS)

clean:
	rm -f *.o *~
