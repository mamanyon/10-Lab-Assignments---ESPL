# All Targets
all: bubblesort hexaPrint

libs: asm-lib c-lib

# Executable "run" depends on the files main.o, add.o and numbers.o.

hexaPrint: hexaPrint.o
	gcc -m32 -g -Wall -o hexaPrint hexaPrint.o

hexaPrint.o: hexaPrint.c
	gcc -g -Wall -m32 -ansi -c -o hexaPrint.o hexaPrint.c

bubblesort:  bubblesort.o
	gcc -m32 -g -Wall -o bubblesort bubblesort.o

bubblesort.o: bubblesort.c
	gcc -g -Wall -m32 -ansi -c -o bubblesort.o bubblesort.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o hello
