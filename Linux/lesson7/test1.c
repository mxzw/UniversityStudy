#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
    printf("命令行参数的个数为:%d\n",argc);

    printf("命令行参数的内容为：");
     for(int i =0 ; i < argc; i++){
          printf("%s\n", argv[i]);
     }
    printf("环境变量的内容为：");

     for(int i =0 ; env[i]; i++){
          printf("%s\n", env[i]);
     }
      return 0;

}


