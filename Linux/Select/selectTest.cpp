#include <stdio.h>
#include <unistd.h>

#include <sys/select.h>
#include <iostream>

using namespace std;

/*
 * 将0号文件描述符设置到readfds监控事件中，
 * 一旦监控到该文件描述符就绪，就对其进行打印
 *
 */
int main()
{
    fd_set readfds;

    __FD_ZERO(&readfds);
    __FD_SET(0,&readfds);

    while(1)
    {
        int fdNum = select(1,&readfds,NULL,NULL,NULL);
        if(fdNum < 0)
        {
            cout << "select failed" << endl;
            continue;
        }

        if(__FD_ISSET(0,&readfds))
        {
            char buf[1024] = {0};
            read(0,buf,sizeof(buf)-1);
            printf("%s\n",buf);
        }
    }

    return 0;
}
