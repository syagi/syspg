#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
    FILE *fp;
    int a;
    int offset;
    char *endptr;

    if(argc!=4){
        fprintf(stderr,"Usage: %s <i> <j> <k>\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    fp=fopen("int_bin","rb");

    offset=
      strtol(argv[1],&endptr,10)*
      strtol(argv[2],&endptr,10)*
      strtol(argv[3],&endptr,10);
    fseek(fp,offset,SEEK_SET);
    fread(&a,sizeof(int),1,fp);
    printf("%d",a);
    
}