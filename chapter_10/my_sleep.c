#include <signal.h>
#include <unistd.h>

void sig_handler(int singno)
{
    puts("handler SIGALRM");
}

size_t my_sleep(size_t second) {
    if (signal(SIGALRM, sig_handler) == SIG_ERR) {
        return second;
    }

    alarm(second);
    pause();
    return alarm(0);
}

int main(int argc, char const* argv[]) {
    my_sleep(3);

    return 0;
}

