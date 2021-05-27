#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>

#define key 0x86868686

int main()
{
    int shmid = shmget(key,1024,IPC_CREAT | 0664);

    void* addr = shmat(shmid,NULL,0);

    puts("It's start to read string in share memory");
    printf("%s\n",(char*)addr);

    shmdt(addr);


    puts("read end");


    return 0;
}
