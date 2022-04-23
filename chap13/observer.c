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
    union semun inival;
    struct sembuf semlock;
    struct shmid_ds buf;

    semlock.sem_num=0;
    semlock.sem_flg=0;
    srand((unsigned) time(NULL));

    if(argc!=3){
        fprintf(stderr,"usage: %s ida idb\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    ida = atoi(argv[1]);
    idb = atoi(argv[2]);

    a = (int *) shmat(ida,0,0);
    b = (int *) shmat(idb,0,0);

    for(i=0;i<100;i++){
        printf("a=%d, b=%d\n",*a,*b);
        printf("a+b= %d\n",*a+*b);
        sleep(1);
    }
}