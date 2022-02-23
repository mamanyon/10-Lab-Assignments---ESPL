all: prog

prog: prog.o Open.o Close.o
	gcc -m32 -o prog prog.o Open.o Close.o

prog.o: prog.c
	gcc -m32 -c -o prog.o prog.c

Open.o: Open.asm
	nasm -g -f elf -w+all -o Open.o Open.asm

Close.o: Close.asm
	nasm -g -f elf -w+all -o Close.o Close.asm
clean:
	rm -rf *.o prog