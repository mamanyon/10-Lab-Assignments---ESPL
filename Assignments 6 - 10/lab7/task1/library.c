#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "LineParser.h"



char *history[10];
int arrcurr = 0;
int flag = 0;


void cd_exec(cmdLine *pCmdLine){
    if(!pCmdLine->arguments[1] || !strcmp(pCmdLine->arguments[1], "~")){
        char *home = getenv("HOME");
        if(chdir(home) != 0){
            perror("chdir failed: HOME");
        }
        return;
    }
    if(chdir(pCmdLine->arguments[1]) != 0){
        char *str = strcat("chdir failed: ", pCmdLine->arguments[1]);
        perror(str);
    }
}

void update_array(char* command){
    if(arrcurr > 9){
        flag = 1;
    }
    char *copy = (malloc(strlen(command)));
    strcpy(copy, command);
    history[arrcurr % 10] = copy;
    arrcurr += 1;
}

void handle_history(){
    if(!flag){
        int i;
        for (i = 0; i < arrcurr; i++){
            printf("%s", history[i]);
        }
    }
    else{
        int i;
        for (i = arrcurr % 10; i < 10; i++) {
            printf("%s", history[i]);
        }
        for (i = 0; i < arrcurr % 10; i++) {
            printf("%s", history[i]);
        }
    }
}

void execute(cmdLine *pCmdLine){
    int status;
    while(pCmdLine != NULL){
        if(!strcmp(pCmdLine->arguments[0], "cd")){
            cd_exec(pCmdLine);
            return;
        }
        if(pCmdLine->outputRedirect){

        }
        int cpid = fork();
        if (cpid == -1){
            perror("forking failed");
            exit(EXIT_FAILURE);
        }
        if (cpid == 0){ /*code execued by child*/
            if(pCmdLine->inputRedirect){
                int fd0 = open(pCmdLine->inputRedirect, O_RDONLY);
                if(fd0 < 0){
                    perror("open error");
                    exit(EXIT_FAILURE);
                }
                dup2(fd0, 0);
            }
            if(pCmdLine->outputRedirect){
                int fd1 = open(pCmdLine->outputRedirect, O_CREAT|O_RDWR, 0666);
                if(fd1 < 0){
                    perror("Can't open file");
                    exit(EXIT_FAILURE);
                }
                dup2(fd1, 1);
            }
            if(!strcmp(pCmdLine->arguments[0], "history")){
                handle_history();
                _exit(EXIT_SUCCESS);
            }
            int exec_flag = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
            if(exec_flag == -1){
                perror("execvp() error");
                _exit(EXIT_FAILURE);
            }
        }
        else{
            if(pCmdLine->blocking){/*code execued by parent*/
                waitpid(cpid, &status, 0);
            }
        }
        pCmdLine = pCmdLine->next;
    }

}

int main() {
    char cwd[PATH_MAX];
    FILE *fout = stdout;
    FILE *fin = stdin;
    while(1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            fprintf(fout, "%s > ", cwd);
        } else {
            perror("getcwd() error");
            return 1;
        }
        char command[MAX_ARGUMENTS];
        fgets(command, MAX_ARGUMENTS, fin);
        if(!strcmp(command, "quit\n")){
            break;
        }
        else if(command[0] == '!'){
            if(command[1] - '0' >= arrcurr ){
                perror("no such command exists!");
            }
            strcpy(command, history[command[1] - '0']);
        }
        update_array(command);
        cmdLine *cmd = parseCmdLines(command);
        execute(cmd);
        freeCmdLines(cmd);
    }
    int i;
    for (i = 0; i < 10; ++i) {
        if(!history[i]){
            free(history[i]);
        }
    }
    return 0;
}
