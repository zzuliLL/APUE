#include<fcntl.h>
#include "apue.h"

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char *argv[])
{
    umask(0);
    if(creat("test1", RWRWRW) == -1)
        err_sys("creat test1 error");
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if(creat("test2", RWRWRW) == -2)
        err_sys("creat test2 error");
    return 0;
}

