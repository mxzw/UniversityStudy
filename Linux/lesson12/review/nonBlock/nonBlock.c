#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    int pipeid = pipe(fd);
    if(pipeid < 0)
    {
        perror("create pipe failed");
        return 0;
    }

    //获取读端的文件描述符属性
    puts("It's test to read_fd");
    int flag_read = fcntl(fd[0],F_GETFL); 
    printf("before set read fd ,flag = %d\n",flag_read);

    fcntl(fd[0],F_SETFL,flag_read | O_NONBLOCK);
    flag_read = fcntl(fd[0],F_GETFL); 
    printf("after set read fd ,flag = %d\n",flag_read);
    puts("read test over.\n");

    //获取写端的文件描述符属性
    puts("It's test to write_fd");
    int flag_write = fcntl(fd[1],F_GETFL); 
    printf("before set write fd ,flag = %d\n",flag_write);

    fcntl(fd[1],F_SETFL,flag_write | O_NONBLOCK);
    flag_write = fcntl(fd[1],F_GETFL); 
    printf("after set write fd ,flag = %d\n",flag_write);
    puts("write test over.");
    
    return 0;
}
