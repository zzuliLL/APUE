#include<fcntl.h>
#include<unistd.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        err_exit("Usage: ./a.out <pathname>\n");
    }
    if(access(argv[1], R_OK) == -1) err_print("access R_OK failed");
    else printf("access R_OK success\n");

    if(access(argv[1], W_OK) == -1) err_print("access W_OK failed");
    else puts("access W_OK success");
    return 0;
}

