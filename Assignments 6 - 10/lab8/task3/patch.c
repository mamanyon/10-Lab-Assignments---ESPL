
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char** argv) {
    int size = atoi(argv[3]);
    int dest_pos = (int)strtol(argv[2], NULL, 16);
    int source_pos = (int)strtol(argv[5], NULL, 16);
    int fd;
    int fd2;
    fd = open(argv[1], O_RDONLY);
    fd2 = open(argv[4], O_RDONLY);
    if (fd < 0 || fd2 < 0) {
        fprintf(stderr, "%s: can't open %s or %s\n", argv[0], argv[1], argv[4]);
        perror("open");
        exit(1);
    }
    struct stat st;
    fstat(fd, &st);
    struct stat st2;
    fstat(fd2, &st2);
    int fileLen = st.st_size;
    int fileLen2 = st2.st_size;
    printf("%x\n", fileLen);
    char *p = mmap(NULL, fileLen, PROT_READ, MAP_PRIVATE, fd, 0);
    char *p2 = mmap(NULL, fileLen2, PROT_WRITE, MAP_PRIVATE, fd2, 0);
    memcpy(p2+dest_pos, p+source_pos, size);
    return 0;
}