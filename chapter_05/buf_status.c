#include "apue.h"

void print_status(const char *name, FILE *fp)
{
    printf("stream = %s", name);
    if(fp->_flags & _IO_UNBUFFERED)
        printf(", unbuffered");
    else if(fp->_flags & _IO_LINE_BUF)
        printf(", linebuf");
    else printf(", full buf");
    printf(", bufsize = %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

int main()
{
    if(fgetc(stdin) == EOF)
        err_sys("failed initial stdin");
    if(fputs("init stdout\n", stdout) == EOF)
        err_sys("failed initial stdout");
    if(fputs("init stderr\n", stderr) == EOF)
        err_sys("failed initial stderr");
    FILE *fp = fopen("/etc/passwd", "r");
    if(fp == NULL)
        err_sys("failed initial /etc/passwd");
    print_status("stdin", stdin);
    print_status("stdout", stdout);
    print_status("stderr", stderr);
    print_status("/etc/passwd", fp);
    return 0;

}

