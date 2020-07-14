OPTS =	-Wall -pedantic -g -std=gnu99

all: chip8 clean

chip8:	main.o cpu.o errs.o stack.o
	gcc $(OPTS) -o chip8 main.o cpu.o errs.o stack.o

main.o:
	gcc $(OPTS) -c main.c

cpu.o:
	gcc $(OPTS) -c cpu.c

errs.o:
	gcc $(OPTS) -c errs.c

stack.o:
	gcc $(OPTS) -c stack.c

clean:
	rm -f *.o *~ 	
