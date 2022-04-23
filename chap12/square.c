#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

void chop(char *);

int main(){
    char str[256];
    int fd[2];
    pid_t ret;
    int status;

    if (pipe (fd) < 0){
        perror ("pipe");
        exit(EXIT_FAILURE);
    }

    ret = fork();

    if(ret==0){
        read(fd[0],str,sizeof(str));
        sprintf(str, "%.0f", pow(atoi(str),2));
        write(fd[1],str,sizeof(str));

    }
    if(ret>0){
        fgets(str,sizeof(str),stdin);
        chop(str);
        write(fd[1],str,sizeof(str));
        wait(&status);
        read(fd[0],str,sizeof(str));
        printf("%s\n",str);
    }
}
void chop(char *str){
    str[strlen(str)-1]='\0';
}