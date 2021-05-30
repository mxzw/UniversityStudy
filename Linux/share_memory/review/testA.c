#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define key 0x86868686

int main()
{
    puts("start to testA to write shm");
    int shmid = shmget(key,1024,IPC_CREAT | 0664);

    void* addr = shmat(shmid,NULL,0);

    sprintf((char*)addr,"It's test to share memory，I am testA");
    puts("end to testA to write shm");

    while(1)
    {
        sleep(1);
    }


    return 0;
}
