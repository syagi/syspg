#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char** argv){
    int id,sid;
    char *adr;
    union semun inival;
    struct sembuf semlock;

    if(argc!=2){
        fprintf(stderr, "Usage: %s <shm ID>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    id=atoi(argv[1]);
    if ((int)(adr=(char*)shmat(id,(void*)0,0))==-1){
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    else {
        if((sid=semget(id,1,IPC_CREAT|0700))==-1){
            perror("semget");
            exit(EXIT_FAILURE);
        }
        while(1){
            semlock.sem_num=0;
            semlock.sem_op=-1;
            if(semop(sid,&semlock,1)<0) break;
            printf("Input any Strings>");
            fgets(adr,512,stdin);
            adr[strlen(adr)-1]='\0';
            if(strcmp(adr,"quit")==0){
                break;
            }
            semlock.sem_num=0;
            semlock.sem_op=1;
            if(semop(sid,&semlock,1)<0) break;
            sleep(3);
        }
        if(shmdt(adr)==-1){
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
        if (semctl(sid,IPC_RMID,0)==-1) perror("semctl");
    }
}