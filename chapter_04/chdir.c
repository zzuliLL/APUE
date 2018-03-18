#include<unistd.h>
#include "apue.h"

// qie huan dang qian work dir
int main(int argc, char *argv[])
{
    if(chdir("/tmp") == -1) err_sys("chdir()");
    else puts("success");
    return 0;
}

