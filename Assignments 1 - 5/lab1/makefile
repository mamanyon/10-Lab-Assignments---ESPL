# All Targets
all: char2ascii

libs: c-lib

char2ascii:  task2.o task1a.o task1b.o task1c.o
	gcc -m32 -g -Wall -o char2ascii task2.o task1a.o task1b.o task1c.o

task1a.o: task1a.c
	gcc -g -Wall -m32 -ansi -c -o task1a.o task1a.c

task1b.o: task1b.c
	gcc -g -Wall -m32 -ansi -c -o task1b.o task1b.c

task1c.o: task1c.c
	gcc -g -Wall -m32 -ansi -c -o task1c.o task1c.c

task2.o: task2.c
	gcc -g -Wall -m32 -ansi -c -o task2.o task2.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -f *.o char2ascii
