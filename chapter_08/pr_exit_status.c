#include "apue.h"
#include<sys/wait.h>
#include<unistd.h>

void pr_status(int status)
{
    if(WIFEXITED(status))
    {
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status))
    {
        printf("abnormal termination, signal number = %d", WTERMSIG(status));

#ifdef WCOREDUMP
        if(WCOREDUMP(status))
            printf("(core file generated)");
#endif // WCOREDUMP
        printf("\n");
    }
    else if(WIFSTOPPED(status))
    {
        printf("child stopped, signal number = %d\n", WIFSTOPPED(status));
    }
    else err_sys("unknown status");

}

int main()
{
    int status;
    pid_t pid;
    pid = fork();
    if(pid < 0) err_sys("fork");
    else if(pid == 0) exit(7);
    if(wait(&status) != pid)
        err_sys("wait1");
    else
        pr_status(status);

    pid = fork();
    if(pid < 0) err_sys("fork");
    else if(pid == 0) abort();
    if(wait(&status) != pid)
        err_sys("wait2");
    else
        pr_status(status);

    pid = fork();
    if(pid < 0) err_sys("fork");
    else if(pid == 0) status /= 0;
    if(wait(&status) != pid)
        err_sys("wait3");
    else
        pr_status(status);

    return 0;
}

