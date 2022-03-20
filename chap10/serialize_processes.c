#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int main(){
    pid_t ret;
    int i;
    int status;

    printf("[BEFORE FORK]\n");
    printf("Process ID: %d\t Parent Process ID: %d\n", getpid(), getppid());
    ret=fork();
    srand(time(NULL));
    printf("[AFTER FORK]\n");
    printf("Process ID: %d\t Parent Process ID: %d\n", getpid(), getppid());

    printf("[id=%d] Return Value of fork : %d\n", getpid(),ret);
    puts("");

    sleep(1);

    if(ret>0){
        wait(&status);
    }

    for(i=0; i<5; i++){
        printf("(%d) for loop i=%d\n", getpid(), i);
        sleep( rand() % 3);
    }
    if(ret==0){
        printf ("(%d) End the child process\n", getpid());
    }
    else if(ret>0){
        printf ("(%d) End the parent process\n", getpid());
    }
    else {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
}