#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int i)
{
    printf("signal Id is:%d\n",i);
}

int main()
{
    signal(2,sigcallback);
    signal(40,sigcallback);
    sigset_t set;

    sigaddset(&set,2);
    sigaddset(&set,40);
    int ret = sigprocmask(SIG_BLOCK,&set,NULL);
    if(ret < 0)
    {
        perror("sigprocmask failed");
        return 0;
    }
    puts("test start!");
    getchar();
    
    ret = sigprocmask(SIG_UNBLOCK,&set,NULL);

    while(1)
    {
        sleep(1);
    }
    return 0;
}
