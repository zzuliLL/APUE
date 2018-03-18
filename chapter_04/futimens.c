#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    if(argc != 2) err_exit("Usage: ./a.out <filename>");
    struct stat buf;
    if(stat(argv[1], &buf) == -1) err_sys("stat");
    int fd = open(argv[1], O_TRUNC);
    if(fd == -1) err_sys("open");
    struct timespec times[2];
    times[0] = buf.st_atim;
    times[1] = buf.st_mtim;
    if(futimens(fd, times) == -1) err_sys("futimes error");
    close(fd);
    return 0;

}

