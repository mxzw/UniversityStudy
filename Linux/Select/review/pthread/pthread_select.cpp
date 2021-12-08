#include <unistd.h>
#include <sys/select.h>
#include <pthread.h>

#include <iostream>

using namespace std;

void* PthreadEntry(void* arg)
{
    pthread_detach(pthread_self());
    fd_set *readfds = (fd_set*) arg;
    
    while(1)
    {
        int ret = select(1,readfds,NULL,NULL,0);
        if(ret < 0)
        {
           cout << "select failed" << endl;
           continue;
        }

        if(FD_ISSET(0,readfds))
        {
            char buf[1024] = {0};
            read(0,buf,sizeof(buf)-1);
            cout << buf << endl;
        }
    }

    return NULL;
}

int main()
{
    pthread_t pid;
    
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);

    for(int i = 0; i < 2; ++i)
    {
        int ret = pthread_create(&pid,NULL,PthreadEntry,(void *)&readfds);
        if(ret < 0)
        {
            cout << "pthread_create failed" << endl;
            continue;
        }
    }

    while(1)
    {
        sleep(1);
    }
    return 0;
}
