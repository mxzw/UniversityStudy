#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int fd = open("./1.txt",O_RDWR | O_CREAT,0664);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }

    //将标准输出重定向至当前文件，表示当进行输出的时候，会将内容打印到1.txt中，而不是打印在屏幕上
    //将oldfd拷贝于newfd
    dup2(fd,1);

    int count = 10;


    while(count--)
    {
        //重复打印10次到1.txt中
        printf("It's test to redirect!\n");
        //fflush()
        sleep(1);
    }
    return 0;
}
