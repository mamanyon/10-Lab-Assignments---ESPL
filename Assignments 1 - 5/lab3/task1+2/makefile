# All Targets
all: bcmp

libs:c-lib

# Executable "run" depends on the files main.o, add.o and numbers.o.

bcmp: bcmp.o
	gcc -m32 -g -Wall -o bcmp bcmp.o

bcmp.o: bcmp.c
	gcc -g -Wall -m32 -ansi -c -o bcmp.o bcmp.c

#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o hello
