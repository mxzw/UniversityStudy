// 2019.3.14
// 利用数组和函数重载求5个数最大值
//（分别考虑整数、单精度、长整数的情况）。
/* 函数重载是指在同一作用域内，
可以有一组具有相同函数名，
不同参数列表的函数，
这组函数被称为重载函数。
重载函数通常用来命名一组功能相似的函数，
这样做减少了函数名的数量，
避免了名字空间的污染，
对于程序的可读性有很大的好处。*/
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

