#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addr5;
int addr6;

int foo();
void point_at(void *p);

int main (int argc, char** argv){
    int addr2;
    int addr3;
    char* yos="ree";
    int * addr4 = (int*)(malloc(50));
    printf("- &addr2: %p - stack\n",&addr2);
    printf("- &addr3: %p - stack\n",&addr3);
    printf("- foo: %p- text segment\n ",foo);
    printf("- &addr5: %p - uninitialized data segment\n",&addr5);
    
	point_at(&addr5);
	
    printf("- &addr6: %p\n - uninitialized data segment",&addr6);
    printf("- yos: %p - rodata =above text segment bellow data segment\n",yos);
    //&yos located on the stackkkk !
	printf("- addr4: %p - heap\n",addr4);
    printf("- &addr4: %p - right value ref on the stack\n",&addr4);
    return 0;
}

int foo(){
    return -1;
}

void point_at(void *p){
    int local;
    static int addr0 = 2;
    static int addr1;


    long dist1 = (size_t)&addr6 - (size_t)p;// -4 (both on the bss = uninitialized data)
					// 5 higher than 6		
    long dist2 = (size_t)&local - (size_t)p;
    long dist3 = (size_t)&foo - (size_t)p;
    
    printf("dist1: (size_t)&addr6 - (size_t)p: %ld\n",dist1);
    printf("dist2: (size_t)&local - (size_t)p: %ld\n",dist2);
    printf("dist3: (size_t)&foo - (size_t)p:  %ld\n",dist3);
	
	printf("- addr0: %p - initialized data segment\n", & addr0);
    printf("- addr1: %p - uninitialized data segment\n",&addr1);
	//both statics so data segment- addr1 higher than addr0
	// -> uninitialized higher than initialized
}

