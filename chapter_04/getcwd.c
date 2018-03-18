#include<unistd.h>
#include "apue.h"

#define BUF_SIZE 4096

//get cur dir

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    if(getcwd(buf, BUF_SIZE) == NULL) err_sys("getcwd");
    printf("path: %s\n", buf);

    if(chdir("/tmp") == -1) err_sys("chdir()");
    if(getcwd(buf, BUF_SIZE) == NULL) err_sys("getcwd");
    printf("path: %s\n", buf);

    return 0;
}

