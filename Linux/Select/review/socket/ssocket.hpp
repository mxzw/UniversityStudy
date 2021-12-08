#include <sys/select.h>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class SocketSelect{
    public:
        SocketSelect()
        {
            FD_ZERO(&readfds_);
            nfds_ = 0;
        }

        void SetFd(int fd)
        {
            FD_SET(fd,&readfds_);

            if(fd > nfds_)
                nfds_ = fd;
        }

        void RmFd(int fd)
        {
            FD_CLR(fd,&readfds_);

            for(int i = nfds_; i >= 0; ++i)
            {
                if(FD_ISSET(i,&readfds_))
                {
                    nfds_ = i;
                    break;
                }
            }
        }

        int SelectWait(vector<int>& iv)
        {
            fd_set tmp = readfds_;
            int ret = select(nfds_+1,&tmp,NULL,NULL,NULL);
            if(ret < 0)
            {
                printf("select failed\n");
                return -1;
            }

            for(int i = 0; i <= nfds_; ++i)
            {
                if(FD_ISSET(i,&tmp))
                    iv.push_back(i);
            }

            return ret;
        }

        ~SocketSelect()
        {
            FD_ZERO(&readfds_);
        }
    private:
        int nfds_;
        fd_set readfds_;
};
