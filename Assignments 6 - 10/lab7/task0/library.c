#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void mypipe(){
    int pipefd[2];
    int cpid;
    char wr[5];
    char *buf = "Hello";
    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if(cpid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(cpid ==0){ /*child process*/
        close(pipefd[0]);
        write(pipefd[1], buf, strlen(buf));
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else{
        close(pipefd[1]);
        while (read(pipefd[0], &wr, 1) > 0){
            write(STDOUT_FILENO, &wr, 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    }
}


int main(int argc, char *argv[]) {
    mypipe();
    return 0;
}