#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int i)
{
    printf("verify signal Id is : %d\n",i);
}

int main()
{

    signal(2,sigcallback);
    signal(40,sigcallback);

    sigset_t set;
    //设置set位图为满
    sigfillset(&set);

    sigset_t oldset;
    //调用sigprocmask函数将所有信号都设置为阻塞
    int ret = sigprocmask(SIG_SETMASK,&set,&oldset);
    if(ret < 0)
    {
        perror("first sigprocmask failed");
        return 0;
    }
    
    getchar();

    ret = sigprocmask(SIG_SETMASK,&oldset,NULL);
    if(ret < 0)
    {
        perror("second sigprocmask failed");
        return 0;
    }



    while(1)
    {
        sleep(1);
    }
    return 0;
}
