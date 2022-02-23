#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void task1a(FILE* input, FILE* output){
    char c;
    while((c = fgetc(input))!= EOF){
        if(c != '\n'){
            fprintf(output, "%d ", c);
        }
        else{
            fprintf(output, "%c", c);
        }
    }
}