#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void task1c(FILE* input, FILE* output){
    char c;
    while((c = fgetc(input))!= EOF){
        if(c != '\n'){
            if(c >= 'A' && c <= 'Z'){
                c -= 'A' - 'a';
            }
            else if(c >= 'a' && c <= 'z'){
                c += 'A' - 'a';
            }
            fprintf(output, "%c", c);
        }
        else{
            fprintf(output, "%c", c);
        }
    }
}
