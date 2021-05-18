#include <stdio.h>

#include <unistd.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return 0;
    }

    int r = fork();
    if(r < 0)
    {
        perror("fork");
        return 0;
    }
    else if(r == 0)
    {
        //child
        close(fd[1]);
        char buf[1024] = {0};
        read(fd[0],buf,sizeof(buf)-1);
        printf("%s",buf);
    }
    else
    {
        //father
        close(fd[0]);
        write(fd[1],"i am father",12);
    }
    return 0;
}
