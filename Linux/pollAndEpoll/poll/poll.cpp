#include <unistd.h>
#include <poll.h>

#include <iostream>
using namespace std;


int main()
{
    struct pollfd fds[10];
    fds[0].fd = 0;
    fds[0].events = POLLIN;

    while(1)
    {
        int ret = poll(fds,1,-1);
        if(ret < 0)
        {
            cout << "poll failed" << endl;
            break;
        }

        for(int i = 0; i < 10; ++i)
        {
            if(fds[i].revents == POLLIN)
            {
                char buf[1024] = {0};
                read(fds[i].fd,buf,sizeof(buf)-1);

                printf("%s\n",buf);
            }
        }
    }
    return 0;
}
