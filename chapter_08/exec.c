#include "apue.h"
#include<unistd.h>
#include<sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
        err_sys("fork");
    else if(pid == 0)
    {
        if(execle("/home/sll/桌面/apue/chapter_08/echoall", "echoall", "myarg1", "MY ARG2", (char*)0, env_init) < 0)
            err_sys("execle");
    }
    if(waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid");

    if((pid = fork()) < 0)
        err_sys("fork");
    else if(pid == 0)
    {
        if(execlp("/home/sll/桌面/apue/chapter_08/echoall", "echoall", "only 1 arg", (char*)0) < 0)
            err_sys("execlp");
    }
    return 0;
}

