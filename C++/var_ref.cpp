// 2019.3.14
//  将变量的引用作为函数形参，
//     实现2个int型数据交换。
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
 
