//2019.3.14
// �������� 2
#include<iostream>
using namespace std;
//������Ķ����������ط���
//�ڴ˴�������غ�����ʹ�ó���Ҫ�����������
int max(int a,int b){
	if( b > a ) a = b;
	cout << "int compare ";
	return a;
} 
double max(double a,double b){
	if( b > a ) a = b;
	cout << "double compare ";
	return a;
}




int main()
{
cout<<max(4,5)<<endl;
cout<<max(45.23,2.3)<<endl;
    return 0;
}
