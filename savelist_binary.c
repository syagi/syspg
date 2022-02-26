#include<stdio.h>
#include<stdlib.h>
#define NAMELEN 18

typedef struct profile
{
    char name[NAMELEN];
    int age;
    float height;
} profile;

int main(int argc, char **argv){
    FILE *fp;
    profile list[4]={
        {"Takako Toyota", 25, 163.42},
        {"Mizuho Kagami", 21, 155.89},
        {"Yoshie Tanaka", 25, 168.23},
        {"Mai Nobe", 22, 145.89}
    };

    if((fp=fopen("list_binary.bin","wb"))==NULL){
        perror("list_binary");
        exit(EXIT_FAILURE);
    }
    fwrite(list,sizeof(profile),4,fp);

    if (fclose(fp)==EOF){
        perror("list_binary");
        exit(EXIT_FAILURE);
    }
    
}