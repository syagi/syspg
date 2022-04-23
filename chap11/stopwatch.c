#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int time;
void count();
void stop();

int main(){
    signal (SIGINT,stop);
    while(1){
        count();
    }
}

void count(){
    time=0;
    while(1){
        sleep(1);
        time++;
        printf (".");
        fflush(stdout);
    }
}

void stop(){
    int ans;
    printf("TIME: %d seconds\n",time);
    printf("[r]estart, [q]uit\n");

    while(1){
        ans=getchar();
        getchar();
        if(ans=='r'){
            break;
        }
        else if(ans=='q'){
            exit(EXIT_SUCCESS);
        }
    }
}