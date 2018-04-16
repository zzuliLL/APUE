#include "apue.h"
#include<signal.h>
#include<unistd.h>


void quit_func(int signo)
{
    printf("caught SIGQUIT\n");
    if(signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        err_sys("signal");
}

int main()
{
    if(signal(SIGQUIT, quit_func) == SIG_ERR)
        err_sys("signal");
    sigset_t new_mask, old_mask;
    if(sigemptyset(&new_mask) < 0)
        err_sys("sigemptyset");
    if(sigaddset(&new_mask, SIGQUIT) < 0)
        err_sys("sigaddset");
    if(sigprocmask(SIG_BLOCK, &new_mask, &old_mask) < 0)
        err_sys("sigprocmask");
    printf("blocked SIGQUIT\n");

    sleep(5);

    sigset_t pend_mask;
    if(sigpending(&pend_mask) < 0)
        err_sys("sigpending");
    if(sigismember(&pend_mask, SIGQUIT))
        printf("SIGQUIT pending\n");
    if(sigprocmask(SIG_SETMASK, &old_mask, NULL) < 0)
        err_sys("sigprocmask");
    printf("SIGQUIT unblock\n");
    return 0;

}

