#include "apue.h"
#include<unistd.h>

char buf[] = "write system-call output\n";
int g_val = 1;

int main()
{
    int val = 2;
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        err_sys("write");

    printf("stdout output\n");

    pid_t pid = fork();
    if(pid == -1)
        err_sys("fork");
    else if(pid)
        sleep(2);
    else g_val++, val++;
    printf("pid = %ld, glob = %d, val = %d\n", (long)getpid(), g_val, val);
    return 0;
}

