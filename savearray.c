#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
    int a[50][50][50];
    FILE *fpa, *fpb;
    int i,j,k;

    fpa=fopen("int_text","w");
    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            for(k=0;k<50;k++){
                a[i][j][k]=rand();
                fprintf(fpa,"%d\n",a[i][j][k]);
            }
        }
    }
    fclose(fpa);

    fpb=fopen("int_bin","wb");
    fwrite(&a,sizeof(int),50*50*50,fpb);
    fclose(fpb);
    
}