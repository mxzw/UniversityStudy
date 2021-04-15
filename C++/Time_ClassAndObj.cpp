// 2019.3.4
// Time类和对象
/*  定义类Time，Time有3个公用的数据成员hour、min、sec分别表示小时、分、秒。
在主函数main中定义Time类对象t1，
在主函数main中输入t1的各数据成员再并输出各数据成员。 */
#include<iostream>
using namespace std;
class Time{
public:
	int hour(int a){
		return a;
	}
	int min(int b){
		return b;
	}
	int sec(int c){
		return c;
	}
};
int main()
{
	Time t1;
	int x,y,z,j,i,k;
	cin>>x>>y>>z;
	j = t1.hour(x);
	i = t1.min(y);
	k = t1.sec(z);
	cout<<j<<":"<<i<<":"<<k; 
	return 0;
}
