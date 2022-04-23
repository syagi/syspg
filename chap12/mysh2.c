#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>


#define BUFSIZE 512

int pipesplit(char *str, char **commands);
int argsplit (char *str, char **argv);
void chop(char *str);

int main(){
    pid_t ret;
    int status, cnt=0;
    int i,pipes;
    int fd[2];
    char str[BUFSIZE];
    char *commands[2];
    char *argv[20];
    while(1){
        printf("mysh[%d]>",cnt++);
        if(fgets(str, BUFSIZE,stdin)==NULL){
            perror(str);
            exit(EXIT_FAILURE);
        }
        chop(str);
        pipes = pipesplit(str, commands);

        if (pipe (fd) < 0){
            perror ("pipe");
            exit(EXIT_FAILURE);
        }

        for(i=0;i<=pipes;i++){
            argsplit(commands[i], argv);
            if(strcmp(argv[0],"quit")==0){
                break;
            }
            ret=fork();
            if(ret==0){
                if(i==0){
                    close(1);
                    if(dup(fd[1])!=1){
                        perror("dup failed");
                        close(fd[1]);
                        exit(EXIT_FAILURE);
                    }
                }
                else {
                    close(0);
                    if(dup(fd[0])!=0){
                        perror("dup failed");
                        close(fd[0]);
                        exit(EXIT_FAILURE);
                    }
                }
                execvp(argv[0],argv);
                break;
            }
            if(ret>0){
                wait(&status);
                fprintf(stderr,"[%d] Exit\n",ret);
            } else {
                perror("fork");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int pipesplit(char *str, char **commands){
    int i;
    commands[0]=strtok(str,"|");
    for(i=1;i<2;i++){
        commands[i]=strtok(NULL,"|");
        if(commands[i]==NULL){
            break;
        }
    }
    return i-1;
}

int argsplit(char *str, char **argv){
    int i;
    argv[0]=strtok(str," ");
    for(i=1;i<20;i++){
        argv[i]=strtok(NULL," ");
        if(argv[i]==NULL){
            break;
        }
    }
    return i-1;
}

void chop(char *str){
    str[strlen(str)-1]='\0';
}