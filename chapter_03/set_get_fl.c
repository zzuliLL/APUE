#include<fcntl.h>
#include<unistd.h>
#include "apue.h"


void set_fl(int fd, int flags)
{
    int val = fcntl(fd, F_GETFL, 0);
    if(val == -1) err_sys("getfl error");
    if(fcntl(fd, F_SETFL, val|flags) == -1)
        err_sys("setfl error");
}

void clr_fl(int fd, int flags)
{
    int val = fcntl(fd, F_GETFL, 0);
    if(val == -1) err_sys("getfl error");
    if(fcntl(fd, F_SETFL, val&(~flags)) == -1)
        err_sys("setfl error");
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: a.out <descriptor#>\n");
        exit(1);
    }
    set_fl(atoi(argv[1]), atoi(argv[2]));
    clr_fl(atoi(argv[1]), atoi(argv[2]));
    return 0;
}


