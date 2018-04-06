#include "apue.h"
#include<unistd.h>

void charatatime(char *s)
{
    setbuf(stdout, NULL);   // set unbuffered
    char *p;
    for(p = s; *p != '\0'; p++)
        putc(*p, stdout);
}

int main()
{
    pid_t pid = fork();
    if(pid) charatatime("output from parent!\n");
    else charatatime("output from child!\n");
    return 0;
}

