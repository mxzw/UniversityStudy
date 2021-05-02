#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // int open(const char *pathname, int flags); 若打开的文件存在
    //  int open(const char *pathname, int flags, mode_t mode); 若不存在
    int fd = open("bite",O_RDWR | O_CREAT,0664);

    //ssize_t write(int fd, const void *buf, size_t count);
    char buf1[] = "i like linux";
    write(fd,buf1,sizeof(buf1)-1);

    //注意，这里需要将文件的指针重新设置在文件开头，用lseek函数
    //off_t lseek(int fd, off_t offset, int whence);


    lseek(fd,0,SEEK_SET);

    char buf2[1024] = {0};
    //ssize_t read(int fd, void *buf, size_t count);
    int a = read(fd,buf2,sizeof(buf2));
    printf("%s\n",buf2);
    printf("%d\n",a);

    close(fd);

    return 0;
}
