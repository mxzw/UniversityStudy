#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int i)
{
    printf("signal is %d\n",i);
}

int main()
{
    signal(SIGINT,sigcb);

    while(1)
    {
        sleep(1);
    }

    return 0;
}
