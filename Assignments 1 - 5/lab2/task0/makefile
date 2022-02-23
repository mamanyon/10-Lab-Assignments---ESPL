# All Targets
all: Run

libs: asm-lib c-lib

Run:  count-words.o
	gcc -m32 -g -Wall -o Run count-words.o

count-words.o: count-words.c
	gcc -g -Wall -m32 -ansi -c -o count-words.o count-words.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean: 
	rm -f *.o hello
