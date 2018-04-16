#include "apue.h"
#include<signal.h>
#include<unistd.h>

void sig_usr(int signo)
{
    if(signo == SIGUSR1)
        printf("signal is SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("signal is SIGUSR2\n");
    else
        err_sys("unknown signal");
}

int main()
{
    signal(SIGUSR1, sig_usr);
    signal(SIGUSR2, sig_usr);
    for( ; ; )
    {
        pause();
    }
    return 0;
}

