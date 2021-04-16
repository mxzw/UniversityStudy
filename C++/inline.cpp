// 2019.3.14
// 内联函数 
#include<iostream>
 using namespace std;
//不允许改动程序其它地方。
//在此处添加内联函数，使得程序按要求正常输出。 
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
