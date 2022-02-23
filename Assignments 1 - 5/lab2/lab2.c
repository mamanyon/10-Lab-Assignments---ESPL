/* $Id: count-words.c 858 2010-02-21 10:26:22Z tolpin $ */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* return string "word" if the count is 1 or "words" otherwise */
char *words(int count) {
    char *words = malloc(10);
    strcpy(words, "words");
  if(count==1) 
    words[strlen(words)-1] = '\0';
  return words;
}

/* print a message reporting the number of words */
int print_word_count(char **argv) {
  int count = 0;
  char **a = argv;
  while(*(a++))
    ++count;
  char *w = words(count);
  printf("The sentence contains %d %s.\n", count, w);
  free(w);
  return count;
}

/* print the number of words in the command line and
 return the number as the exit code */
int main(int argc, char **argv) {
    return print_word_count(argv+1);
}

   
______________________________________________________________________
______________________________________________________________________



/* task 2a functions here - from prev lab */
void echo_printer(char c){
    printf("%c", c);
}
void ascii_printer(char c){
    if(c == '\n'){
        return;
    }
    printf("%d", c);
}

void charToBinary(char c, int num[8]){
    int n = (int) c;
    int index = 7;
    while(index >= 0){
        num[index] = n & 1;
        index --;
        n >>= 1;
    }
}
void binary_printer(char c){
    int num[8];
    charToBinary(c, num);
    int i;
    for(i = 0; i < 8; i++){
        printf("%d",num[i]);
    }
}
void lower_to_upper_printer(char c){
    if(c >= 'A' && c <= 'Z'){
        c -= 'A' - 'a';
    }
    else if(c >= 'a' && c <= 'z'){
        c += 'A' - 'a';
    }
    printf("%c", c);
}
////////example for a function as argument to another func
void string_printer(char* str, void (*func_ptr) (char)){
    int i;
    for (i = 0; i < strlen(str); i++){
        if(str[i] == '\n'){
            printf("%c", '\n');
            continue;
        }
        (*func_ptr)(str[i]);
        if(i < strlen(str) - 1){
            printf(" ");
        }
    }
}

void string_reader(char* s){
    fgets(s, 10, stdin);
}

void bitwise_or(char* s){
    int now = s[0];
    int i;
    for(i = 1; i < strlen(s); i++){
        if(s[i] == '\n'){
            continue;
        }
        now = now|(int)s[i];
    }
    char c = now;
    binary_printer(c);
    printf("%c", '\n');
}
struct fun_desc{
    char *name;
    void (*fun)(char);
};
int main(int argc, char **argv) {
    struct fun_desc menu[] = {{"echo printer",&echo_printer},
                              {"ASCII printer",&ascii_printer},
                              {"binary printer",&binary_printer},
                              {"lower to upper",&lower_to_upper_printer}};
    printf("%s", "Please enter a string(0<size<=10): \n");
    char input[10];
    string_reader(input);
    char c = '0';
    char line[256];
    int len = sizeof (menu)/sizeof (menu[0]);
    while (!feof(stdin)) {
        printf("%s", "Please choose printer type: \n");
        int i;
        for(i = 0; i < len; i++){
            printf("%d) %s \n", i, menu[i].name);
        }
        printf("4) bitwise or \n");
        fgets(line,sizeof line, stdin);
        c = line[0];
        if(c < '0' || c > '4'){
            if(feof(stdin)){
                break;
            }
            printf("Please select 0-4 or CTRL-D to exit. \n");
            continue;
        }
        if(feof(stdin)){
            break;
        }
        if(c == '4'){
            bitwise_or(input);
            printf("%c", '\n');
            printf("%s", "--------------------------------- \n");
            continue;
        }
        string_printer(input,menu[c - '0'].fun);
        printf("%s", "--------------------------------- \n");
    }
    printf("DONE. \n");
    return 0;
}