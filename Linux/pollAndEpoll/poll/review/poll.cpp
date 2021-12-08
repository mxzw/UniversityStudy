#include <unistd.h>
#include <poll.h>

#include <iostream>

using namespace std;


int main()
{
    struct pollfd pollfd[1];
    pollfd[0].fd = 0;
    pollfd[0].events = POLLIN;
    
    while(1)
    {
        int res = poll(pollfd,1,-1);
        if(res < 0)
        {
            cout << "poll failed" << endl;
            return 0;
        }

        for(int i = 0; i < 1; ++i)
        {
            if(pollfd[i].revents == POLLIN)
            {
                char buf[1024] = {0};
                read(pollfd[i].fd,buf,sizeof(buf)-1);
                cout << buf << endl;
            }
        }
    }


    return 0;
}
