// 2019.3.14
//  ��������������Ϊ�����βΣ�
//     ʵ��2��int�����ݽ�����
#include<iostream>
using namespace std;
inline void change(int &a,int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int main()
{
	int x,y;
	cin >> x >> y;
	cout << x << " " << y << endl;
	change(x,y);
	cout << x << " " << y << endl;
	return 0;
}
 
