#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/param.h>
#include<sys/ucred.h>
#include<sys/mount.h>
#include<util.h>

int main(){
    long mntsize;
    struct statfs *mntbuf;
    int i;

    mntsize = getmntinfo(&mntbuf, MNT_WAIT);
    printf("\n");
    printf("     Filesystem (from -> to)                        512-blocks\n");
    for(i=0;i<mntsize;i++){
        printf("%17s -> %27s\t%lld\n",mntbuf[i].f_mntfromname, mntbuf[i].f_mntonname, mntbuf[1].f_blocks);
    }
    printf("\n");
}