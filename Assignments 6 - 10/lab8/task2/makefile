# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clean rdelf

rdelf: task2.o
	gcc  $(LINK_FLAGS) -o rdelf task2.o

task2.o : task2.c
	gcc  $(C_COMPILE_FLAGS) -o task2.o task2.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -rf *.o rdelf
