//2019.3.14
// ��Ĭ���β�ֵ�ĺ���
#include<iostream>
using namespace std;
//������Ķ����������ط���
//������غ�����ʵ������������ӣ��������ò���Ĭ��ֵ��ʹ�ó���Ҫ�����������
    int add(int a,int b){
    	return a+a+b+b;
	}
	int add(int a){
		return a+1+a+1+a-2+a-2;
	}
	int add(int a,int b,int c){
		return a+b+c;
	}
	 
 

int main() 
 {
    cout<<add(1,4)<<endl;
    cout<<add(3)<<endl;
    cout<<add(1,2,3)<<endl;
    return 0;
}
