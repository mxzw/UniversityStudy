/* int main(int argc,char*argv[]);
 * argc:�����в����ĸ�����
 * argv:�ַ���ָ�����飬���ָ��ֱ�ָ�����������������͸����������ַ�����
 * ����argv��0��ָ���������ַ�����argc��ȡֵΪ��������+1; 
��̬�ڴ���� ----  ͷ�ļ� ��stdlib.h��
   * void*malloc(size_t size)��
    ��ϵͳ�����СΪsize���ڴ�飬��ָ���׵�ַ��ָ�뷵�ء�������벻�ɹ�������NULL��
   * void free(void*block);
    �ͷ���malloc()������ڴ�顣block��ָ��˿��׵�ַ��ָ�루malloc()�ķ���ֵ��
   *���ڶ�̬������ڴ�
    1.�ڶ��з��䣬�������
	2.�� free/delete֮ǰ��������Ч
	3.�ڱ�free/delete֮�󣬸ÿ��ڴ治�������� */ 
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

��������������:
������ ����1 ����2
��ô 
argnum  ֵΪ3
args[0] ֵΪ��ĳ�����(��ȫ��·��,�ַ���)
args[1] ֵΪ ����1 (�ַ���)
args[2] ֵΪ ����2 (�ַ���) */
