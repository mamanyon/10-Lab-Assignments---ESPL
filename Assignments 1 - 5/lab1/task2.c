
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void task1a(FILE* input, FILE* output);
void task1b(FILE* input, FILE* output);
void task1c(FILE* input, FILE* output);

int main(int argc, char **argv) {
    FILE * output = stdout;
    FILE * input = stdin;
    int i;
    int flag = 0;
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i],"-o")==0)
            output = fopen(argv[++i],"w");
        else if(strcmp(argv[i],"-i")==0)
            input = fopen(argv[++i], "r");
        else if (strcmp(argv[i],"-b")==0){
            flag = 1;//to binary
        }
        else if((strcmp(argv[i],"-c")==0)) {
            flag = 2;//upper case or lower case
        }
    }
    if(flag == 1){
        task1b(input, output);
    }
    else if(flag == 2){
        task1c(input, output);
    }
    else{
        task1a(input, output);
    }
    fprintf(output, "%c", '\n');
    fclose(output);
    return 0;
}



