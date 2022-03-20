#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char *gen_string();

int main(){
    char *str;
    str=gen_string();

    printf("input any key\n");
    getchar();
    printf("generated string\t%s\n",str);
    free(str);
}

char * gen_string(){
    /* array を heap領域に確保 */
    char *array=(char *)malloc(sizeof(char)*8);
    int i;
    srand(time(NULL));
    for(i=0;i<8;i++){
        array[i]=rand()%('z'-'A')+'A';
    }
    return array;
}