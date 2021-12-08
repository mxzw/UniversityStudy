#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>

#include <iostream>
#include <vector>

using namespace std;

class SelectHead{
    public:
        SelectHead()
        {
            FD_ZERO(&readfds_);
            max_size_ = -1;
        }

        ~SelectHead()
        {
            FD_ZERO(&readfds_);
        }
        
        void Set(int fd)
        {
            FD_SET(fd,&readfds_);

            if(fd > max_size_)
            {
                max_size_ = fd;
            }
        }


        void Del(int fd)
        {
            __FD_CLR(fd,&readfds_);

            //删除之后要记得判断max_size_是否需要进行重置。
            for(int i = max_size_; i >= 0; ++i)
            {
                if(__FD_ISSET(i,&readfds_))
                {
                    max_size_ = i;
                    break;
                }
            }
        }

        int SelectWait(vector<int>& iv)
        {
            //这里记得要拿tmp去进行select，因为select一旦成功，
            //则会将未就绪的文件描述符移出事件集合中
            
            fd_set tmp = readfds_;

            int ret = select(max_size_ + 1,&tmp,NULL,NULL,NULL);
            if(ret < 0)
            {
                perror("select");
                return -1;
            }

            for(int i = 0;i <= max_size_ ; ++i)
            {
                if(__FD_ISSET(i,&tmp))
                {
                    iv.push_back(i);
                }
            }


            return ret;
        }


    private:
        int max_size_;

        fd_set readfds_;

};
