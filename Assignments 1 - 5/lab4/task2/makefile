all: scmp1 scmp2

scmp1: scmp.o cmpstr.o
	gcc -m32 -o scmp1 scmp.o cmpstr.o

scmp2: scmp.o cmpstr2.o
	gcc -m32 -o scmp2 scmp.o cmpstr2.o

cmpstr.o: cmpstr.c
	gcc -m32 -c -o cmpstr.o cmpstr.c

scmp.o: scmp.c
	gcc -m32 -c -o scmp.o scmp.c

cmpstr2.o: cmpstr.asm
	nasm -g -f elf -w+all -o cmpstr2.o cmpstr.asm
.PHONY: clean

clean:
	rm -rf *.o scmp1