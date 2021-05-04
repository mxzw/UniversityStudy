#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
    while(1)
    {
        printf("[minishell@localhost]$ ");
        //stdout 是C库extern(声明) FILE *stdout -->是一个文件流指针
        //由于没有‘\‘ 来刷新缓冲区，因此采用fflush强制刷新缓冲区
        fflush(stdout);

        char buf[1024] = {0};
        //char *fgets(char *s, int size, FILE *stream);
        fgets(buf,sizeof(buf)- 1,stdin);

        //当按下回车时，会读入一个'\n'进入缓冲区
        if(strlen(buf)== 0 || buf[0]== '\n')
        {
            continue;
        }

        //由于按下回车后，读入的是'\n'，因此需要在末尾加上'\0'
        buf[strlen(buf)-1] = '\0';

        pid_t pid = fork();

        if(pid < 0)
        {
            perror("fork error\n");
            continue;
        }
        else if(pid==0)
        {
            //child
            //首先在buf中，区分出命令行参数和命令程序
            printf("%s\n",buf);

            char* argv[1024] = {0};
            int pos = 0;
            char* begin = buf;
            char* end = buf;

            while(*end!= '\0')
            {
                //首先将end指针放在第一个间隔处（空格）,第一个即为命令程序
                while(*end != ' ' && *end != '\0')
                {
                    end++;
                }

                argv[pos] = begin;
                pos++;
                //若此时就只有一个命令程序，没有参数，那么end就会指向最后buf字符串结尾
                if(*end == '\0')
                {
                    break;
                }
                else
                {
                    //若还有参数，则将end的当前位置置为'\0'，作为存入argv数组中字符串的结束符
                    *end = '\0';
                    end++;
                    begin = end;
                }
            }
            //当end结束后，说明给argv数组已经分配好值了
    //        printf("pos:%d\n",pos);
            argv[pos] = NULL;

            //然后就进行进程程序替换，将其替换为你想要的执行的命令
            execvp(argv[0],argv);
            exit(1);
        }
        else
        {
            //father
            wait(NULL);
        }


    }
    return 0;
}
