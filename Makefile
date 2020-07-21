CC = gcc
OPTS =	-Wall -pedantic -g -w -std=gnu99
SRC_OBJ = src/main.c src/chip8.c src/graphics.c src/input.c src/sound.c src/timer.c src/debug.c src/exit.c
TST_OBJ = test/main.c

all:	chip8 chip8_test clean

%.o: %.c
	$(CC) -lncurses -c -o $@ $< $(OPTS)

chip8: $(SRC_OBJ)
	$(CC) -o $@ $^ $(OPTS)

chip8_test: $(TST_OBJ)
	$(CC) -o $@ $^ $(OPTS)

clean:
	rm -f *.o *~
