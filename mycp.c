#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
  FILE *fpin, *fpout;
  char buf;

  if (argc<3){
    fprintf(stderr, "Usage: copy <from> <to>\n");
    exit(EXIT_FAILURE);
  }

  if((fpin = fopen(argv[1],"r"))==NULL){
    perror("argv[1]");
    exit(EXIT_FAILURE);
  }
  if((fpout = fopen(argv[2],"w"))==NULL){
    perror("argv[2]");
    exit(EXIT_FAILURE);
  }

  buf=fgetc(fpin);
  while(buf!=EOF){
    fputc(buf,fpout);
    buf=fgetc(fpin);
  }
  if(ferror(fpin)!=0){
    perror("mycp");
    exit(EXIT_FAILURE);
  }
}
