%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

all: lwca

lwca: start.o print.o w.o utoa_s.o cmpstr.o ws.o
	ld  -melf_i386 -o $@ $^

clean:
	rm -f *.o lwca
