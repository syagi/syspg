#include<stdio.h>

int main(){
    /* sizeof(int) * 1500000 = 6MiB 
       スタック領域をはみ出して確保しようとするため、seg fault する */
    int a[1500000];
    int b[1500000];
    int c=0;
    printf("&a=%x, &b=%x, &c=%x\n", a, b, &c);
}