#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define BUFFSIZE 512
#define NAMELEN 24
#define PROFNUM 20

typedef struct profile
{
    char name[NAMELEN];
    int age;
} profile;


int main (int argc, char **argv){
    FILE *fpin;
    char tok;
    char buff[BUFFSIZE];
    char *endptr;
    profile prof[PROFNUM];
    int i,j;

    if(argc!=2){
        fprintf(stderr,"Usage: %s <profile_csv>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if((fpin=fopen(argv[1],"r"))==NULL){
        perror("argv[1]");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<PROFNUM;i++){
        if(fgets(buff,BUFFSIZE-1,fpin)==NULL){
            break;
        }
        //fprintf(stderr,"D[buff]: %s\n",buff);
        // get name
        for(j=0;j<NAMELEN;j++){
            if(buff[j]==','){
                prof[i].name[j]='\0';
                break;
            }
            else {
               prof[i].name[j]=buff[j];
            }
        }
        // get age
        //fprintf(stderr,"D[j]: %d\n",j);
        //fprintf(stderr,"D[buff+j]: %s\n",buff+j+1);
        prof[i].age=strtol(buff+j+1,&endptr,10);
    }
    // print profile
    for(j=0;j<i;j++){
        printf("[NO.%d]\n",j);
        printf("name=%s\n",prof[j].name);
        printf("age=%d\n",prof[j].age);
    }
}
