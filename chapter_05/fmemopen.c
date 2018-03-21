#include "apue.h"
#include<unistd.h>

#define BUF_SIZE 4096

int main(void)
{
    char buf[BUF_SIZE] = "hello world!\n";
    FILE *fp = fmemopen(buf, BUF_SIZE, "r");
    char ch;
    while((ch = fgetc(fp)) != EOF)
        fputc(ch, stdout);
    fclose(fp);
    return 0;
}

