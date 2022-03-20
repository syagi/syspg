#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>

int main(int argc, char** argv){
    DIR *directory;
    struct dirent *ent;
    char path[255];
    struct stat st;

    if (argc!=2){
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    directory = opendir(argv[1]);
    if(!directory){
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    while ((ent = readdir(directory)) !=NULL ){
        //printf("%s",&ent->d_name[strlen(ent->d_name)-1]);
        if(ent->d_name[strlen(ent->d_name)-1]=='~'){
          snprintf(path,255,"%s/%s",argv[1],ent->d_name);
          printf("delete %s\n",path);
          unlink(path);
        }
    }
    closedir(directory);
}