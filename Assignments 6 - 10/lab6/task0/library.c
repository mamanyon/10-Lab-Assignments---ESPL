#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>
#include "LineParser.h"
#include <string.h>
void execute(cmdLine *pCmdLine){
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof (cwd));
    int j = execvp(pCmdLine->arguments[0], pCmdLine->arguments);
    if(j == -1){
        perror("execv() error");
    }
}

int main() {
    char cwd[PATH_MAX];
    FILE *fout = stdout;
    FILE *fin = stdin;
    while(1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            fprintf(fout, "%s>", cwd);
        } else {
            perror("getcwd() error");
            return 1;
        }

        char command[2048];
        fgets(command, 2048, fin);
        if(!strcmp(command, "quit\n")){
            break;
        }
        cmdLine *cmd = parseCmdLines(command);
        execute(cmd);
        freeCmdLines(cmd);
    }
    return 0;
}