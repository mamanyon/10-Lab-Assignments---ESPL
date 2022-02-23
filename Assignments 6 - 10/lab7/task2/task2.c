#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void printmessage(char* message, int flag){
    if(flag == 0){
        return;
    }
    fprintf(stderr,"%s\n", message);
}

void mypipeline(char* com1[], char* com2[], int flag){
    int pipefd[2];
    int cpid1;
    int cpid2;
    int status;
    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printmessage("parent_process>forking...", flag);
    cpid1 = fork();
    if(cpid1 == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(cpid1 ==0) { /*child process*/
        printmessage("child1>redirecting stdout to the write end of the pipe...", flag);
        close(1);
        dup(pipefd[1]);
        close(pipefd[1]);
        printmessage("child1>going to execute cmd...", flag);
        execvp(com1[0], com1);
    }
    else{
        printmessage("parent_process>created process...", flag);
        printmessage("parent_process>closing write end of the pipe...", flag);
        close(pipefd[1]);
        cpid2 = fork();
        if(cpid2 == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if(cpid2 ==0){
            printmessage("child2>redirecting stdin to the write end of the pipe...", flag);
            close(0);
            dup(pipefd[0]);
            close(pipefd[0]);
            printmessage("child2>going to execute cmd...", flag);
            execvp(com2[0], com2);
        }
        else{
            printmessage("parent_process>closing read end of the pipe...", flag);
            close(pipefd[0]);
            printmessage("parent_process>waiting for child process to eliminate...", flag);
            waitpid(cpid1, &status, 0);
            waitpid(cpid2, &status, 0);
            printmessage("parent_process>exiting...", flag);
        }
    }
}

int main(int argc, char *argv[]) {
    int flag = 0;
    if(argc > 1){
        if(!strcmp(argv[1], "-d")){
            flag = 1;
        }
    }
    char *com1[] = {"ls", "-l", NULL};
    char *com2[] = {"tail", "-n", "2", NULL};
    mypipeline(com1, com2, flag);
    return 0;
}

