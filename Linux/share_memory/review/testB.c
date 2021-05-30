#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define key 0x86868686

int main()
{
    puts("start to testB to read shm");
    int shmid = shmget(key,1024,IPC_CREAT | 0664);

    void* addr = shmat(shmid,NULL,0);

    printf("%s\n",(char*)addr);
    puts("end to testB to read shm");

    shmctl(shmid,IPC_RMID,NULL);



    return 0;
}
