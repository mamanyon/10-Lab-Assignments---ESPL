#include <stdlib.h>
#include <stdio.h>

extern int funcA(char* ch1);

int cmpstr(char *s1, char *s2){
    int i = 0;
    while(1){
        if(s1[i] == '\0' || s2[i] == '\0'){
            return s1[i] - s2[i];
        }
        int bool = s1[i] - s2[i];
        if(!bool){
            i++;
            continue;
        }
        return bool;
    }
}

