#include "apue.h"
#include<setjmp.h>

static jmp_buf buf;
int g_val = 5;

void f1()
{
    longjmp(buf, 1);
}

int main()
{
    int autoval = 1;
    register int regival = 2;
    volatile int volaval = 3;
    static int statval = 4;
    if(setjmp(buf) != 0)
    {
        puts("after longjmp");
        printf("local value: %d\n", autoval);
        printf("register value: %d\n", regival);
        printf("volatile value: %d\n", volaval);
        printf("static value: %d\n", statval);
        printf("global value: %d\n", g_val);
        exit(0);
    }
    puts("before longjmp");
    printf("local value: %d\n", autoval);
    printf("register value: %d\n", regival);
    printf("volatile value: %d\n", volaval);
    printf("static value: %d\n", statval);
    printf("global value: %d\n", g_val);
    puts("");

    autoval = 10;
    regival = 11;
    volaval = 12;
    statval = 13;
    g_val = 14;
    
    f1();
    return 0;
}

