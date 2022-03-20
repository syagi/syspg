#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>

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
        snprintf(path,255,"%s/%s",argv[1],ent->d_name);
        if(lstat(path,&st)<0){
            perror(path);
            exit(EXIT_FAILURE);
        }
        switch (st.st_mode & S_IFMT){
            case S_IFDIR:
              printf("%s/\n",ent->d_name);
              break;
            case S_IFLNK:
              printf("%s@\n",ent->d_name);
              break;
            default:
              printf("%s\n",ent->d_name);
        }
    }
    closedir(directory);
}