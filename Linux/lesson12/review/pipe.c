#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    int pipefd = pipe(fd);
    if(pipefd == -1)
    {
        perror("pipe");
        return 0;
    }

    int forkid = fork();
    if(forkid < 0)
    {
        perror("fork");
        return 0;
    }
    else if(forkid == 0)
    {
        //child
        puts("It's start to child read!");
        //子进程只进行读，不进行写，就关闭写端
         close(fd[1]);
        char buf2[1024] = {0};
        read(fd[0],buf2,sizeof(buf2)-1);

        printf("%s\n",buf2);
        puts("It's end to child read!");

    }
    else
    {
        //father
        puts("It's start to father write!");
        //父进程只进行写，不进行读，就关闭读端
        close(fd[0]);
        char buf1[1024] = {0};
        sprintf(buf1,"i am father,my PID is %d\n",getpid());
        write(fd[1],buf1,strlen(buf1));
        puts("It's end to father write!");
    }
    while(1)
    {
        sleep(1);
    }
    return 0;
}
