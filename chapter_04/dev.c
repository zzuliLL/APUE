#include<sys/stat.h>
#include "apue.h"

int main(int argc, char *argv[])
{
    int i;
    struct stat buf;
    for(i = 1; i < argc; i++)
    {
        printf("%s: ", argv[i]);
        if(stat(argv[i], &buf) == -1) err_sys("stat() error");
        printf("dev: %d/%d", major(buf.st_dev), minor(buf.st_dev));
        if(S_ISBLK(buf.st_mode) || S_ISCHR(buf.st_mode))
            printf(", rdev: %d/%d", major(buf.st_rdev), minor(buf.st_rdev));
        printf("\n");
    }
    return 0;
}

