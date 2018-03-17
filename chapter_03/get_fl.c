#include<fcntl.h>
#include<unistd.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: a.out <descriptor#>\n");
        exit(1);
    }
    int val = fcntl(atoi(argv[1]), F_GETFL, 0);
    if(val == -1)
        err_sys("fcntl error");

    switch(val & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only\n");
        break;
    case O_WRONLY:
        puts("write only");
        break;
    case O_RDWR:
        puts("read write");
        break;
    default:
        err_exit("unknown access mode");
    }
    if(val & O_APPEND) puts("append");
    if(val & O_NONBLOCK) puts("nonblocking");
    if(val & O_SYNC) puts("sync");
    return 0;
}

//1 > temp.foo

