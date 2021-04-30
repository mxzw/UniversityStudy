#include<stdio.h>
#include<unistd.h>
int main()
{
    printf("test process replace to  start!\n");
    printf("before replace...\n");

    char* argv[1024] = {0};
    argv[0] = "ls";
    argv[1] = "-l";
    argv[2] = "-a";
    argv[3] = NULL;
    execvp("ls",argv);

    printf("after replace...\n");
    return 0;
}
