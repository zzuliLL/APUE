#include "apue.h"
#include<signal.h>
#include<setjmp.h>
#include<unistd.h>


static sig_atomic_t canjmp = 0;
sigjmp_buf buf;


void sig_usr(int signo) {

}

void sig_alrm(int signo)
{
    if(canjmp == 0)
        return ;
    siglongjmp(buf, 1);
}


void pr_mask(char *msg)
{
    fputs(msg, stdout);
    sigset_t s;
    if(sigpending(&s) < 0)
        err_sys("sigpending");
    int i;
    for(i = 0; i < NSIG; i++)
    {
        if(sigismember(&s, i))
            printf("%d ", i);
    }
    fputc('\n', stdout);
    fflush(stdout);
}

int main()
{
    if(signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal");
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("signal");

    pr_mask("starting main: ");

    alarm(1);
    if(sigsetjmp(buf, 1))
    {
        pr_mask("end of main: ");
        exit(0);
    }
    canjmp = 1;
    for( ; ; )
        pause();
    return 0;

}

