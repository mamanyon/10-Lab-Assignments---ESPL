# flags
C_COMPILE_FLAGS = -g -Wall -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clean my_shell

my_shell: LineParser.o library.o
	gcc  $(LINK_FLAGS) -o my_shell LineParser.o library.o

LineParser.o : LineParser.c
	gcc  $(C_COMPILE_FLAGS) -o LineParser.o LineParser.c

library.o : library.c
	gcc  $(C_COMPILE_FLAGS) -o library.o library.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -rf *.o my_shell
