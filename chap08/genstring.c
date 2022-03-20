#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char *gen_string();

int main(){
    char *str;
    str=gen_string();

    printf("input any key\n");
    getchar();
    /* array のあった領域は開放されているので、期待した値が出力されない */
    printf("generated string\t%s\n",str);
}

char * gen_string(){
    /* array は stack領域に確保される */
    char array[8];
    int i;
    srand(time(NULL));
    for(i=0;i<8;i++){
        array[i]=rand()%('z'-'A')+'A';
    }
    /* array のアドレスを返すが、その後解放されてしまうため有効な値が渡されない */
    return array;
}