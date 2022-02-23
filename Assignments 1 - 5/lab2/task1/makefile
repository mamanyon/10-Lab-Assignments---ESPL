# All Targets
all: addresses T1c T2

libs: asm-lib c-lib

# Executable "run" depends on the files main.o, add.o and numbers.o.

addresses:  addresses.o
	gcc -m32 -g -Wall -o Run addresses.o

T1c: T1c.o
	gcc -m32 -g -Wall -o T1c T1c.o

addresses.o: addresses.c
	gcc -g -Wall -m32 -ansi -c -o addresses.o addresses.c

T1c.o: T1c.c
	gcc -g -Wall -m32 -ansi -c -o T1c.o T1c.c

T2: task2.o
	gcc -m32 -g -Wall -o T2 task2.o

task2.o: task2.c
	gcc -g -Wall -m32 -ansi -c -o task2.o task2.c




#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o hello
