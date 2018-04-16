#include "apue.h"
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>


static void my_sigcld(int signo)
{
    signal(SIGCLD, my_sigcld);
    pid_t pid;
    pid = wait(NULL);
    if(pid < 0) err_sys("wait");
    printf("pid = %d\n", pid);
}

int main()
{
    pid_t pid;
    signal(SIGCLD, my_sigcld);
    pid = fork();
    if(pid < 0) err_sys("fork");
    else if(pid == 0)
    {
        sleep(2);
        _exit(0);
    }
    pause();
    return 0;
}

