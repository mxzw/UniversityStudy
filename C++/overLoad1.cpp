// 2019.3.14
// ��������ͺ���������5�������ֵ
//���ֱ��������������ȡ����������������
/* ����������ָ��ͬһ�������ڣ�
������һ�������ͬ��������
��ͬ�����б�ĺ�����
���麯������Ϊ���غ�����
���غ���ͨ����������һ�鹦�����Ƶĺ�����
�����������˺�������������
���������ֿռ����Ⱦ��
���ڳ���Ŀɶ����кܴ�ĺô���*/
#include<iostream>
using namespace std;
int s(int a,int b,int c,int d,int e){
	if( b > a ) a = b;
	if( c > a ) a = c;
	if( d > a ) a = d;
	if( e > a ) a = e;
	return a;
}
float s(float a,float b,float c,float d,float e){
	if( b > a ) a = b;
	if( c > a ) a = c;
	if( d > a ) a = d;
	if( e > a ) a = e;
	return a;
}
long s(long a,long b,long c,long d,long e){
	if( b > a ) a = b;
	if( c > a ) a = c;
	if( d > a ) a = d;
	if( e > a ) a = e;
	return a;
}
int main()
{
	int a,b,c,d,e;
	float f,g,h,i,j;
	long k,l,m,n,o;
	cin >> a >> b >> c >> d >> e;
	cin >> f >> g >> h >> i >> j;
	cin >> k >> l >> m >> n >> o;
	cout << s(a,b,c,d,e) << "\n"
	<< s(f,g,h,i,j) << "\n"
	<< s(k,l,m,n,o) << endl; 
	return 0;
}

