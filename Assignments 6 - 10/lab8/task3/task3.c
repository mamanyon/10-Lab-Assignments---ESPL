#include <stdio.h>
#include <stdlib.h>

int fib(int limit) {
    if(limit < 0)
        return -1;
    if (limit == 1)
        return 0;

    int prev = 0, cur = 1;
    while (prev + cur < limit) {
        int tmp = cur;
        cur = cur + prev;
        prev = tmp;
    }
    return cur;
}
int main(int argc, char **argv){
    int limit = atoi(argv[1]);
    printf("%d\n", fib(limit));
    return 0;
}




