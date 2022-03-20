#include<stdio.h>

void func(){
    char buf[256];
    char c;
    int i=0;
    /* 256文字を超えた入力を受け付けてしまうため、メモリ汚染を起こす*/
    //while ((c=getchar())!=EOF){
    /* 255文字を超えた入力を受け付けないようガードを入れる*/
    while ((c=getchar())!=EOF&&i<255){
        buf[i]=c;
        i++;
    }
    /* NULL文字で終端 */
    buf[i]='\0';
    printf("buf=%s\n",buf);
}

int main() {
    func();
}