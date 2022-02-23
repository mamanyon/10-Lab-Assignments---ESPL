# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clean rdelf

rdelf: task0.o
	gcc  $(LINK_FLAGS) -o rdelf task0.o

task0.o : task0.c
	gcc  $(C_COMPILE_FLAGS) -o task0.o task0.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -rf *.o rdelf
