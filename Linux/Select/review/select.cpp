#include <unistd.h>
#include <sys/select.h>

#include <iostream>

using namespace std;

#define nfds 1

int main()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);
    while(1)
    {
        fd_set tmp = readfds;
        int ret = select(nfds,&tmp,NULL,NULL,NULL);
        if(ret < 0)
        {
            cout << "select failed" << endl;
            return 0;
        }
        for(int i = 0; i < nfds; ++i){
            if(FD_ISSET(0,&tmp))
            {
                char buf[1024] = {0};
                read(0,buf,sizeof(buf)-1);
                cout << buf << endl;
            }
        }
    }


    return 0;
}
