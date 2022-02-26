#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define BASE 10

int main(int argc, char **argv){
  int a, b, c;
  char *endptr;

  if(argc != 3){
    fprintf(stderr,"Usage: %s <num> <num>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  a = strtol(argv[1],&endptr,BASE);
  if (errno == EINVAL || errno == ERANGE){
    perror("ERROR(strtol(argv[1]))");
    exit(EXIT_FAILURE);
  }
  else if (errno != 0){
    perror("Unexpected ERROR(strtol(argv[1]))");
    exit(EXIT_FAILURE);
  }
  else if (*endptr!='\0'){
    fprintf(stderr,"No digit character is found %s\n",argv[1]);
    exit(EXIT_FAILURE);
  }
  b = strtol(argv[2],&endptr,BASE);
  if (errno == EINVAL || errno == ERANGE){
    perror("ERROR(strtol(argv[2]))");
    exit(EXIT_FAILURE);
  }
  else if (errno != 0){
    perror("Unexpected ERROR(strtol(argv[2]))");
    exit(EXIT_FAILURE);
  }
  else if (*endptr!='\0'){
    fprintf(stderr,"No digit character is found %s\n",argv[2]);
    exit(EXIT_FAILURE);
  }
  c = a + b;
  printf ("%d + %d = %d\n",a,b,c);
}
