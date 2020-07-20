OPTS =	-Wall -pedantic -g -w -std=gnu99

all: chip8_test clean

chip8_test:	main.o cpu.o errs.o stack.o display.o
	gcc $(OPTS) -o chip8_test main.o cpu.o errs.o stack.o display.o -lSDL2

main.o:
	gcc $(OPTS) -c main.c

cpu.o:
	gcc $(OPTS) -c ../cpu.c

errs.o:
	gcc $(OPTS) -c ../errs.c

stack.o:
	gcc $(OPTS) -c ../stack.c

display.o:
	gcc $(OPTS) -c ../display.c

clean:
	rm -f *.o *~ 	
