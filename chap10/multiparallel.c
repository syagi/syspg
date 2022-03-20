#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define CHILDLEN 3

int main(){
    pid_t ret[3];
    int i;
    int status;

    printf("[BEFORE FORK]\n");
    printf("Process ID: %d\t Parent Process ID: %d\n", getpid(), getppid());
    ret[0]=fork();
    printf("[AFTER FORK 0]\n");
    printf("Process ID: %d\t Parent Process ID: %d\n", getpid(), getppid());
    printf("[id=%d] Return Value of fork : %d\n", getpid(),ret[0]);
    for(i=1;i<CHILDLEN;i++){
        if(ret[i-1]>0){
            ret[i]=fork();
            printf("[AFTER FORK %d]\n",i);
            printf("Process ID: %d\t Parent Process ID: %d\n", getpid(), getppid());
            printf("[id=%d] Return Value of fork : %d\n", getpid(),ret[i]);
        }else{
            break;
        }
    }
    srand(time(NULL));

    puts("");

    sleep(1);

    for(i=0; i<5; i++){
        printf("(%d) for loop i=%d\n", getpid(), i);
        sleep( rand() % 3);
    }
    for(i=0;i<CHILDLEN;i++){
        if(ret[i]==0){
            printf ("(%d) End the child process\n", getpid());
            return 0;
        }
    }
    printf ("(%d) End the parent process\n", getpid());
}