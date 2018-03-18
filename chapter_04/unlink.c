#include<fcntl.h>
#include<unistd.h>
#include "apue.h"

const char *path = "/home/sll/code/test";

int main(int argc, char *argv[])
{
    int fd = open(path, O_CREAT|O_RDWR);
    if(fd == -1) err_sys("open() error");
    char ch = 'a';
    for(int i = 1; i < 10*1000*1024; i++)
    {
        if(write(fd, &ch, 1) != 1) err_sys("write() error");
    }
    unlink(path);
    puts("unlink");
    sleep(16);
    puts("done");
    return 0;
}

