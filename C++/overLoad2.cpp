//2019.3.14
// 函数重载 2
#include<iostream>
using namespace std;
//不允许改动程序其它地方。
//在此处添加重载函数，使得程序按要求正常输出。
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
