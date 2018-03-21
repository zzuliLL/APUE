#include "apue.h"

#define BUF_SIZE 4096

int main()
{
    char buf[BUF_SIZE];
    while(fgets(buf, BUF_SIZE, stdin) != NULL)
    {
        if(fputs(buf, stdout) == EOF)
            err_sys("fputs error");
    }
    if(ferror(stdin))
        err_sys("input error");
    return 0;

}

