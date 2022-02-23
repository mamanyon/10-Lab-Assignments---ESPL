
#include <stdio.h>

extern int Open(char* filename);
extern int Close(int descriptor);
int main(int argc, char **argv){
    if(argc != 2){
        printf("Please provide filename");
    }
    char* filename = argv[1];
    int desc = Open(filename);
    printf("The corresponding file descriptor is: %d \n", desc);
    int done = Close(desc);
    char* closing_message = "CLOSING DONE\n";
    if(done == -1){
        closing_message = "CLOSIING FAILED\n";
    }
    printf("%s", closing_message);
    return 0;
}
