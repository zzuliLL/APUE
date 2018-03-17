#include<fcntl.h>
#include<unistd.h>
#include "apue.h"

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    while(1)
    {
        int len = read(STDIN_FILENO, buf, BUF_SIZE);
        if(len <= 0) break;
        if(write(STDOUT_FILENO, buf, len) != len)
            err_sys("write error");
    }
    return 0;
}


// < l.c > ll.c

