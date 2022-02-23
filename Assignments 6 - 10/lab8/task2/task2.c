#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    int fd;

    if (argc != 2) {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
        perror("open");
        exit(1);
    }

    struct stat st;
    fstat(fd, &st);
    int fileLen = st.st_size;

    char *p = mmap(NULL, fileLen, PROT_READ, MAP_PRIVATE, fd, 0);
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) p;
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 || ehdr->e_ident[EI_MAG1] != ELFMAG1 || ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not an ELF file!");
        exit(1);
    }
    if (ehdr->e_ident[EI_CLASS] != ELFCLASS32) {
        fprintf(stderr, "Not a 32-bit ELF file!");
        exit(1);
    }
    Elf32_Shdr *shdr = (Elf32_Shdr * )(p + ehdr->e_shoff); /* start of section header*/
    int shnum = ehdr->e_shnum;
    Elf32_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
    char *sh_strtab_p = p + sh_strtab->sh_offset;
    int i;
    for (i = 0; i < shnum; i++) {
        if(shdr[i].sh_type == SHT_SYMTAB){
            Elf32_Sym *symtab = (Elf32_Sym *)(p+shdr[i].sh_offset);
            char* sec_name = sh_strtab_p + shdr[i].sh_name;
            int symbol_num = shdr[i].sh_size/shdr[i].sh_entsize;
            int j;
            char *symbol_names = (char *)(p + shdr[shdr[i].sh_link].sh_offset);
            for (j = 0; j < symbol_num; j++) {
                printf("[%d] 0x%x %d %s %s\n", j, symtab[j].st_value, i, sec_name, symbol_names + symtab[j].st_name);
            }
        }
    }
    return 0;
}