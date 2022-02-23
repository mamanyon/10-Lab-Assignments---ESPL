# flags
C_COMPILE_FLAGS =  -fno-pie -m32 -ansi -c
LINK_FLAGS = -m32 -g -Wall

all: clean pat

pat: patch.o
	gcc  $(LINK_FLAGS) -o pat patch.o

patch.o : patch.c
	gcc  $(C_COMPILE_FLAGS) -o patch.o patch.c


#tell make that "clean" is not a file name!
.PHONY: clean

#Clean the build directory
clean:
	rm -rf *.o pat
