#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = open("./fifo",O_RDWR);
    
    puts("It's start to write fifo");
    write(fd,"i am process A",14);
    puts("write success!");
    while(1)
    {
        sleep(1);
    }
    close(fd);
    return 0;
}


