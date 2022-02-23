#include <stdio.h>
#include <stdlib.h>

int fib(int limit) {
    printf("this is patched!\n");
    return 0;
}
int main(int argc, char **argv){
    int limit = atoi(argv[1]);
    printf("%d\n", fib(limit));
    return 0;
}



