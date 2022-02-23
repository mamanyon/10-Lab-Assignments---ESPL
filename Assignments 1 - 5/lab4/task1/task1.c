#include <stdio.h>

extern int funcA(char* ch1);

int main(int argc, char **argv)
{
    int res;

    if (argc != 2){
        fprintf(stderr,"Usage: task1 string\n");
        return 0;
    }

    char* ch1 = argv[1];

    res = funcA(ch1);

    printf("The length of the input string is: %d\n",res);

    return 0;
}
