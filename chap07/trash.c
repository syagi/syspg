#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<unistd.h>

int main(int argc, char** argv){
    struct stat st;
    char trash[8]="Trash";
    char trashpath[255];

    if (argc!=2){
        fprintf(stderr, "Usage: %s <filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 本来はディレクトリを排除してファイル名のみを格納すべきだが省略
    snprintf(trashpath,255,"%s/%s",trash,argv[1]);
    if(link(argv[1],trashpath)!=0){
        perror(trashpath);
        exit(EXIT_FAILURE);
    }

    if(unlink(argv[1])!=0){
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
}