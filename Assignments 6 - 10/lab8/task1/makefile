# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clean rdelf

rdelf: task1.o
	gcc  $(LINK_FLAGS) -o rdelf task1.o

task1.o : task1.c
	gcc  $(C_COMPILE_FLAGS) -o task1.o task1.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -rf *.o rdelf
