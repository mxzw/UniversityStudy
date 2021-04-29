#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> //其中定义了pid_t
#include <sys/wait.h>


int main()
{
    pid_t ret = fork();
    if(ret < 0)
    {
        //表明没有
        perror("create child process failed!");
    }
    else if(ret == 0)
    {
        //child
        printf("i am child process\n");
        sleep(5);
        exit(1);
    }
    else
    {
        //father;
        int status;
        wait(&status);
        printf("quit single is : %d\n",(status) & 0x7f);
        printf("coredump is : %d\n",(status >> 7) & 0x1);
        printf("exit code is : %d\n",(status >> 8) & 0xff);
    }

    return 0;
}
