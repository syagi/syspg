#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<unistd.h>

#define BUFFER 512

int main()
{
    int id, sid;
    char *adr;
    union semun inival;
    struct sembuf semlock;

    semlock.sem_num=0;
    semlock.sem_flg=0;

    if((id = shmget(IPC_PRIVATE,BUFFER,IPC_CREAT|0666))==-1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    if((sid=semget(id,1,IPC_CREAT|0700))==-1){
        perror("semget");
        exit(EXIT_FAILURE);
    }
    inival.val=1;
    semctl(sid,0,SETVAL,inival);
    printf("Shared memory ID = %d \n",id);

    if((int)(adr=(char*)shmat(id,(void *)0,0))==-1){
        perror("shmat");
        shmctl(id,IPC_RMID,NULL);
        exit(EXIT_FAILURE);
    } else {
        strcpy(adr,"Initial");
        while(1){
            semlock.sem_num=0;
            semlock.sem_op=-1;
            if(semop(sid,&semlock,1)<0) break;
            printf("%s\n",adr);
            if (strcmp(adr,"quit")==0){
                break;
            }
            semlock.sem_num=0;
            semlock.sem_op=1;
            if(semop(sid,&semlock,1)<0) break;
            sleep(3);
        }

        if(shmdt(adr)==-1){
            perror("shmdt");
            shmctl(id,IPC_RMID,NULL);
            exit(EXIT_FAILURE);
        }
    }
    if(shmctl(id,IPC_RMID,NULL)==-1){
        perror("shmctl");
        exit(EXIT_FAILURE);
    }
    if (semctl(sid,IPC_RMID,0)==-1) perror("semctl");
}