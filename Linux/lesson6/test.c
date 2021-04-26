#include<stdio.h>
#include<unistd.h>

int main()
{
    // printf("当前进程的PID为：%d\n",getpid());
    // printf("当前进程的父进程的PID为：%d\n",getppid());

    pid_t ret = vfork();
    //判断当前进程是父进程还是子进程
    if(ret < 0)
    {
        return -1;
    }
    else if(ret == 0)
    {
        //为0则表示为子进程
        //child
        printf("我是子进程，PID为：%d\n",getpid());
        printf("我的父进程PID为：%d\n",getppid());
         while(1)
         {
             printf("-------\n");
             sleep(1);
         }
    }
    else
    {
        //即大于0又不等于0，则表明为父进程
        //father
        printf("我是父进程，PID为：%d\n",getpid());
        printf("我的父进程PID为：%d\n",getppid());
        //查看僵尸进程，要用 ps aux | grep test ,因为./test 中，子进程已经结束，但是父进程还是在前台运行，所以是S+,(后台运行是S),退出的子进程为僵尸进程
        while(1)
        {
            printf("Process test!\n");
            //sleep的头文件为unistd.h
            sleep(1);
        }
    }

    return 0;
}
