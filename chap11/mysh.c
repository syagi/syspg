#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define BUFSIZE 512

int argsplit (char *str, char **argv);
void chop(char *str);

int main(){
    pid_t ret;
    int status, cnt=0;
    char str[BUFSIZE];
    char *argv[20];
    while(1){
        printf("mysh[%d]>",cnt++);
        if(fgets(str, BUFSIZE,stdin)==NULL){
            perror(str);
            exit(EXIT_FAILURE);
        }
        chop(str);
        argsplit(str, argv);
        if(strcmp(argv[0],"quit")==0){
            break;
        }
        ret=fork();
        if(ret==0){
            execvp(argv[0],argv);
        }
        if(ret>0){
            wait(&status);
            fprintf(stderr,"[%d] Exit\n",ret);
        }
        else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
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