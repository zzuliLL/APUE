#include "apue.h"
#include<unistd.h>

int main(void)
{
    char namebuf[] = "/tmp/dirXXXXXX";
    int fd = mkstemp(namebuf);
    if(fd == -1) err_sys("mkstmp error");
    printf("%s\n", namebuf);
    sleep(15);
    unlink(namebuf);
    close(fd);
    return 0;
}

