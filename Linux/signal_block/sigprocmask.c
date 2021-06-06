#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    sigset_t set;
    //设置set位图为满
    sigfillset(&set);
    //调用sigprocmask函数将所有信号都设置为阻塞
    int ret = sigprocmask(SIG_BLOCK,&set,NULL);
    if(ret < 0)
    {
        perror("sigprocmask failed");
        return 0;
    }

    while(1)
    {
        puts("It's test to  sigprocmask");
        sleep(1);
    }
    return 0;
}
