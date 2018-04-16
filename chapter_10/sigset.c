#include<signal.h>
#include<errno.h>

#define SIGBAD(signo) ((signo) < 0  || (signo) >= NSIG)
#define sigemptyset(set) ((set) = 0)
#define sigfillset(set) ((set) = ~0, 0)

typedef long _sigset_t;

int _sigaddset(_sigset_t *set, int signo)
{
    if(SIGBAD(signo))
    {
        errno = EINVAL;
        return -1;
    }
    *set |= 1<<(signo - 1);
    return 0;
}

int _sigdelset(_sigset_t *set, int signo)
{
    if(SIGBAD(signo))
    {
        errno = EINVAL;
        return -1;
    }
    *set &= ~(1<<(signo - 1));
    return 0;
}



int _sigmember(_sigset_t *set, int signo)
{
    if(SIGBAD(signo))
    {
        errno = EINVAL;
        return -1;
    }
    if(*set & (1<<(signo-1))) return 1;
    return 0;
}


