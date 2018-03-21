#include "apue.h"

#define BUF_SIZE 4096

int main(void)
{
    char buf[BUF_SIZE], line[BUF_SIZE];
    tmpnam(buf);
    printf("%s\n", buf);
    FILE *fp = tmpfile();
    if(fp == NULL) err_sys("tmpfile() error");
    if(fputs("out line in the tmpfile", fp) == EOF)
        err_sys("fputs error");
    rewind(fp);
    if(fgets(line, BUF_SIZE, fp) == NULL)
        err_sys("fgets error");
    puts(line);
    fclose(fp);
    return 0;

}

