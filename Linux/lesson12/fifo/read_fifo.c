#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    puts("It's start to read fifo");
    int fd = open("./fifo",O_RDWR);
    
    char buf[1024] = {0};
    read(fd,buf,sizeof(buf)-1);
    printf("%s\n",buf);
    puts("read success!");

    return 0;
}


