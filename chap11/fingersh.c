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
    while(1){
        printf("fingersh[%d]>",cnt++);
        if(fgets(str, BUFSIZE,stdin)==NULL){
            perror(str);
            exit(EXIT_FAILURE);
        }
        chop(str);
        if(strcmp(str,"quit")==0){
            break;
        }
        ret=fork();
        if(ret==0){
            fprintf(stderr,"str: %s\n",str);
            if(strlen(str)==0){
               execlp("finger","finger", NULL);
            }
            else{
               execlp("finger","finger", str, NULL);
            }
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

void chop(char *str){
    str[strlen(str)-1]='\0';
}