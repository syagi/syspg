#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>

double getETime(){
    struct timeval tv;
    gettimeofday (&tv,NULL);
    return tv.tv_sec + (double) tv.tv_usec * 1e-6;    
}

int main (int argc, char **argv){
    int fdin, fdout;
    int bufsize;
    char *c;
    char *endptr;
    double st, en;

    if (argc != 4){
        fprintf(stderr,"Usage: %s <from> <to> <bufsize>", argv[0]);
        exit (EXIT_FAILURE);
    }

    if ((fdin = open(argv[1], O_RDONLY))<0){
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    if((fdout=open(argv[2],O_WRONLY))<0){
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }
    bufsize = strtol(argv[3],&endptr,10);
    c = malloc(sizeof(char)*bufsize);

    st = getETime();
    while(read(fdin, c, bufsize) == 1 ){
        write(fdout, c, bufsize);
    }
    en = getETime();
    close(fdin);
    close(fdout);
    free(c);
    printf("ETime: %.6f\n", en-st);

}