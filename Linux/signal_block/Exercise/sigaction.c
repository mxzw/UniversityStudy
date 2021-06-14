#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int i)
{
    printf("signal is %d\n",i);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = sigcb;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(2,&sa,NULL);

    while(1)
    {
        sleep(1);
    }

    return 0;
}
