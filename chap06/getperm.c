#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char **argv){
    struct stat st;

    if (argc != 2){
        fprintf( stderr, "Usage: %s <file> \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if(lstat (argv[1], &st) <0){
        perror (argv[1]);
        exit(EXIT_FAILURE);
    }

    

}