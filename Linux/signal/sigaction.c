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

    struct sigaction sa;
    sa.sa_handler = sigCallBack;
    //将位图中的比特位情况为0
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(2,&sa,NULL);

    while(1)
    {
        sleep(1);
    }


    return 0;
}
