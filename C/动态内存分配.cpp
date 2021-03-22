/* int main(int argc,char*argv[]);
 * argc:命令行参数的个数。
 * argv:字符型指针数组，其个指针分别指向命令行中命令名和各个参数的字符串。
 * 其中argv【0】指向命令名字符串，argc的取值为参数个数+1; 
动态内存分配 ----  头文件 “stdlib.h”
   * void*malloc(size_t size)；
    向系统申请大小为size的内存块，把指向首地址的指针返回。如果申请不成功，返回NULL。
   * void free(void*block);
    释放由malloc()申请的内存块。block是指向此块首地址的指针（malloc()的返回值）
   *关于动态分配的内存
    1.在堆中分配，内容随机
	2.被 free/delete之前，永久有效
	3.在被free/delete之后，该块内存不再属于你 */ 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char*argv[]){
	int i,len;
	char*str;
	if(argc!=2){
		printf("Usage:inverse<string>\n");
		exit(1);
	}
		len=strlen(argv[1]);
		str=(char*)malloc(len+1);
		for(i=0;i<len;++i){
			str[i]='\0';
			printf("%s\n",str);
			free(str);
			exit(0);
		}				

}
/*int main(int argnum, char* args[])

比如你输入命令:
程序名 参数1 参数2
那么 
argnum  值为3
args[0] 值为你的程序名(含全部路径,字符串)
args[1] 值为 参数1 (字符串)
args[2] 值为 参数2 (字符串) */
