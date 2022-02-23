#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void task1a(FILE* input, FILE* output){
// char 2 ascii 
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
//___________________task1b- char2Binary________________________
void charToBinary(char c, int num[8]){
    int n = (int) c;
    int index = 7;
    while(index >= 0){
        num[index] = n & 1;
        index --;
        n >>= 1;
    }
}
void task1b(FILE* input, FILE* output){
  char c;
  int num[8];
  while((c = fgetc(input))!= EOF){
    if(c != '\n'){
      charToBinary(c,num);
      int i;
      for(i = 0; i < 8; i++){
	    fprintf(output, "%d",num[i]);
      }
      fprintf(output, " ");
    }
    else{
        fprintf(output, "%c", c);
    }
  }
 }
//_____________________task1c-Upper to lower case, lower to upper case _______
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
_______________________________________main____________________

int main(int argc, char **argv) {
    FILE * output = stdout;
    FILE * input = stdin;
    int i;
    int flag = 0;
	//Supporting output and input file -o outputfile
    for(i = 1; i < argc; i++){
        if(strcmp(argv[i],"-o")==0)
            output = fopen(argv[++i],"w");
        else if(strcmp(argv[i],"-i")==0)
	 	//-i read the input from the given file instead of stdin
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



