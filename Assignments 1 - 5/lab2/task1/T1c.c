
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char** argv){
    int iarray[3];
    char carray[3];
    printf("- &iarray: %p -- stack\n",&iarray);
    printf("- &iarray+1: %p\n",&iarray+1); //moved 12 bytes= 3*4 = sizeof each cell * size of int
    printf("- &iarray+1: %p\n",&iarray+2); // moved 24 bytes= 2*(3*4)
printf("- &carray: %p\n",&carray);
    printf("- &carray+1: %p\n",&carray+1);// moved 3 bytes= 3*1
    return 0;
}

