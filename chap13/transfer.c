#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<time.h>
#include<unistd.h>

int main(int argc, char **argv){
    int ida,idb,tmp,sid,i;
    int *a,*b;
    int num;

    srand((unsigned) time(NULL));

    if(argc==1){
        if((ida=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666))==-1){
            perror("shmget");
            exit(EXIT_FAILURE);
        }
        if((idb=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666))==-1){
            perror("shmget");
            exit(EXIT_FAILURE);
        }
    }
    else if(argc==3){
        ida = atoi(argv[1]);
        idb = atoi(argv[2]);
    }else {
        exit(EXIT_FAILURE);
    }

    printf("shared memory ID A = %d, B = %d\n",ida,idb);
    a = (int *) shmat(ida,0,0);
    b = (int *) shmat(idb,0,0);

    *a = 100;
    *b = 0;

    printf("a=%d, b=%d",*a,*b);
    for(i=0;i<100;i++){
        *a -=1;
        *b +=1;
        sleep(rand()%3);
    }
    printf("a=%d, b=%d",*a,*b);
}