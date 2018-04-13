#include "apue.h"
#include<unistd.h>

int main()
{
    pid_t pid = fork();
    if(!pid)
    {
        while(1)
        {
            printf("A background process, PID: %d, PPID: %d, tid: %d\n", getpid(), getppid(), gettid());
            sleep(3);
        }
    }
    else if(pid > 0)
    {
        printf("I am parent process, PID: %d, PPID: %d\n", getpid(), getppid());
        exit(0);
    }
    else err_sys("fork");
    return 0;
}

