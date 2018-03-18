#include<sys/stat.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    struct stat buf;

    if(stat("test1", &buf) == -1) err_sys("stat error");
    if(chmod("test1", (buf.st_mode & ~S_IXGRP) | S_ISGID) == -1)
        err_sys("chmod error");
    if(chmod("test2", S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) == -1)
        err_sys("test2 error");
    return 0;

}

