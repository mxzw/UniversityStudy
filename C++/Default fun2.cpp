// 2019.3.14
// ����Ĭ�ϲ����ĺ���ʵ����2����3�����������ֵ��
#include<iostream>
using namespace std;
inline int max1(int a,int b){
	if( a > b ){
		return a;
	}
	else {
		return b;
	}
}
inline int max2(int a,int b,int c){
	if( c > a ){
		a = c;
	}
	if( b > a ){
		a = b;
	}
	return a;
}
int main()
{
	int x,y,z;
	cin >> x >> y >> z;
	cout << x << " " << y << " " << max1(x,y) << endl;
	cout << x << " " << y << " " << z << " " << max2(x,y,z) << endl;
	return 0;
}
