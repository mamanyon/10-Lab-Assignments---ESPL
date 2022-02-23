all: prog

prog: prog.o utoa_s.o
	gcc -m32 -o prog prog.o utoa_s.o

prog.o: lwc.c
	gcc -m32 -c -o prog.o lwc.c

utoa_s.o: utoa_s.asm
	nasm -g -f elf -w+all -o utoa_s.o utoa_s.asm
clean:
	rm -rf *.o prog