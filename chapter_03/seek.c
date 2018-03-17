#include<unistd.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) err_sys("cannot seek");
    else printf("seek OK\n");
    return 0;
}

