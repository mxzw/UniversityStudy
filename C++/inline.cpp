// 2019.3.14
// �������� 
#include<iostream>
 using namespace std;
//������Ķ����������ط���
//�ڴ˴��������������ʹ�ó���Ҫ����������� 
inline int max(int a,int b){
	if( b > a ) a = b;
	return a;
}

int main()
 {
     cout<<max(3,4)<<endl;
     cout<<max(6,5)<<endl;
     return 0;
 } 
