#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigCallBack(int sig)
{
    printf("It's test to processing the SIGINT signal\n");
}


int main()
{
    printf("test start!\n");
    signal(2,sigCallBack);

    while(1)
    {
        sleep(1);
    }


    return 0;
}
