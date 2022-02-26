#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>


double getETime(){
    struct timeval tv;
    gettimeofday (&tv,NULL);
    return tv.tv_sec + (double) tv.tv_usec * 1e-6;    
}

int main(int argc, char **argv){
    FILE *fpin, *fpout;
    double st, en;
    int bufsize;
    char *c, *endptr;

    if (argc!=4){
        fprintf(stderr,"Usage: %s <from> <to> <bufsize>", argv[0]);
        exit (EXIT_FAILURE);
    }
    
    if((fpin = fopen(argv[1], "rb"))==NULL){
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    if((fpin = fopen(argv[2], "wb"))==NULL){
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }

    bufsize = strtol(argv[3],&endptr,10);
    c = malloc(sizeof(char)*bufsize);

    setvbuf(fpin, NULL, _IOFBF, 4096);
    st = getETime();
    while( fread(c,1,bufsize,fpin) ==1){
        fwrite(c,1,bufsize,fpout);
    }
    en = getETime();

    fclose(fpin);
    fclose(fpout);

    printf("ETime: %.6f\n", en-st);

}