#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char** argv){
    int fd;
    Elf32_Ehdr *ehdr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "%s: can't open %s\n",argv[0], argv[1]);
        perror("open");
        exit(1);
    }

    struct stat st;
    fstat(fd, &st);
    int fileLen = st.st_size;

    ehdr = mmap(NULL, fileLen, PROT_READ, MAP_PRIVATE, fd, 0);
    if(ehdr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    printf("ELF INFORMATION FOR FILE: %s \n", argv[1]);
    printf("ELF HEADER: \n");
    printf("Magic Number Byte 1:                0x%x \n", ehdr->e_ident[EI_MAG1]);
    printf("Magic Number Byte 2:                0x%x \n", ehdr->e_ident[EI_MAG2]);
    printf("Magic Number Byte 3:                0x%x\n", ehdr->e_ident[EI_MAG3]);
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 || ehdr->e_ident[EI_MAG1] != ELFMAG1 || ehdr->e_ident[EI_MAG2] != ELFMAG2 || ehdr->e_ident[EI_MAG3] != ELFMAG3){
        fprintf(stderr, "Not an ELF file!");
        exit(1);
    }
    if(ehdr->e_ident[EI_CLASS] != ELFCLASS32){
        fprintf(stderr, "Not a 32-bit ELF file!");
        exit(1);
    }
    printf("Encoding Scheme:");
    switch (ehdr->e_ident[EI_DATA]) {
        case ELFDATANONE:
            fprintf(stderr, "                INVALID DATA");
            exit(1);
        case ELFDATA2LSB:
            printf("                    2's complement, little endian \n");
            break;
        case ELFDATA2MSB:
            printf("                    2's complement, big endian \n");
    }
    printf("Start address:                      0x%x\n", ehdr->e_entry );
    printf("Section header table offset:        %d (bytes into file)\n", ehdr->e_shoff );
    printf("Number of section header entries:   %d\n", ehdr->e_shnum);
    printf("Size of each section header entry:  %d (bytes) \n", ehdr->e_shentsize);
    printf("Index of the shstrtab:              %d \n", ehdr->e_shstrndx);
    return 0;
}
