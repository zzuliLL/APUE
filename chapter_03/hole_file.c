#include<fcntl.h>
#include<unistd.h>
#include "apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char *argv[])
{
    //int fd = creat("file.hole", FILE_MODE);
    int fd = open("file.hole", O_CREAT | O_RDWR);
    if(fd == -1) err_sys("open error");
    if(write(fd, buf1, strlen(buf1)) != strlen(buf1))
        err_sys("buf1 write error");
    if(lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    if(write(fd, buf2, strlen(buf2)) != strlen(buf2))
        err_sys("buf2 write error");
    close(fd);
    return 0;
}

