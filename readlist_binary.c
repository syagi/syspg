#include<stdio.h>
#include<stdlib.h>
#define NAMELEN 18

typedef struct profile
{
    char name[NAMELEN];
    int age;
    float height;
} profile;

int main(int argc,char **argv){
    FILE *fp;
    profile list[4];
    int i;

    if((fp=fopen("list_binary.bin","rb"))==NULL){
        perror("list_binary");
        exit(EXIT_FAILURE);
    }

    fread(list,sizeof(profile),4,fp);

    for(i=0;i<4;i++){
        printf("%s,%d,%f\n",list[i].name,list[i].age,list[i].height);
    }
}