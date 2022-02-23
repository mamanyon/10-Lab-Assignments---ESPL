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

   
