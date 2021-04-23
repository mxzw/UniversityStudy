#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char* a = (char*) malloc(1024);

    strcpy(a,"hello world");

    printf("%s",a);
    free(a);
    a = NULL;
    free(a);
    return 0;
}
