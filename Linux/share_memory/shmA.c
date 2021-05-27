#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>

#define key 0x86868686

int main()
{
    int shmid = shmget(key,1024,IPC_CREAT | 0664);

    void* addr = shmat(shmid,NULL,0);
    if(addr == NULL)
    {
        perror("shmat");
        return 0;
    }

    puts("It's start to write string in share memory");
    sprintf((char*)addr,"i am poccess A");
    shmdt(addr);
    puts("write end");

    
    return 0;
}
