#include<sys/stat.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    struct stat buf;
    int i;
    for(i = 1; i < argc; i++)
    {
        if(stat(argv[i], &buf) == -1)
        {
            err_sys("stat() error");
            continue;
        }
        printf("%s: ", argv[i]);
        if(S_ISREG(buf.st_mode)) puts("regular file");
        else if(S_ISDIR(buf.st_mode)) puts("directory file");
        else if(S_ISBLK(buf.st_mode)) puts("block special");
        else if(S_ISCHR(buf.st_mode)) puts("character special");
        else if(S_ISLNK(buf.st_mode)) puts("sysmbolic link");
        else if(S_ISFIFO(buf.st_mode)) puts("fifo");
        else if(S_ISSOCK(buf.st_mode)) puts("socket");
        else puts("unknown file");
    }
    return 0;
}


//   /etc/passwd /etc /dev/log /dev/tty  /var/lib/oprofile/opd_pipe /dev/sr0 /dev/cdrom

