// 2019.3.4
// Time类的定义
/* 设计一个时间类Time，私有数据成员有hour(时)、minute(分)、second(秒)； 
公有成员函数有：setHour(int)设置数据成员hour的值（采用12小时制），非法的输入默认为12；
setMinue(int)设置数据成员minute的值，非法输入默认为0；
setSecond(int)设置数据成员second的值，非法输入默认为0；
setTime(int，int，int)设置时、分、秒三个数据成员的值；
 showTime()显示时间对象的值。 
在主函数main()中调用相应成员函数，使得时间对象的值能从键盘接收，并正确显示。
提示：时、分、秒均按2位数值形式显示 。 */
#include<iostream>
using namespace std;
class Time{
private:
	int hour,minute,second;
public:
	int setHour(int a){
		if(a<=12){
			return a;
		}
		else{
			return 12;
		}
	}
	int setMinute(int b){
		if(b<=60){
			return b;
		}
		else{
			return 0;
		}
	}
	int setSecond(int c){
		if(c<=60){
			return c;
		}
		else{
			return 0;
		}
	}
	void setTime(int x,int y,int z){
		hour = x;
		minute = y;
		second = z;			
	}
	void showTime(){
		if(hour<10&&minute>=10&&second>=10){
			cout<<"0"<<hour<<":"<<minute<<":"<<second;
		}
		else if(hour>=10&&minute<10&&second>=10){
			cout<<hour<<":"<<"0"<<minute<<":"<<second;
		}
		else if(hour>=10&&minute>=10&&second<10){
			cout<<hour<<":"<<minute<<":"<<"0"<<second;
		}
		else if(hour<10&&minute<10&&second>=10){
			cout<<"0"<<hour<<":"<<"0"<<minute<<":"<<second;
		}
		else if(hour<10&&minute<10&&second<10){
			cout<<"0"<<hour<<":"<<"0"<<minute<<":"<<"0"<<second;
		}
		else if(hour>=10&&minute<10&&second<10){
			cout<<hour<<":"<<"0"<<minute<<":"<<"0"<<second;
		}
		else if(hour<10&&minute>=10&&second<10){
			cout<<"0"<<hour<<":"<<minute<<":"<<"0"<<second;
		}
		else{
			cout<<hour<<":"<<minute<<":"<<second;
		}
	}
};
int main()
{
	Time myTime;
	int i,j,k,o,m,p;
	cin>>i>>j>>k;
	o = myTime.setHour(i);
	m = myTime.setMinute(j);
	p = myTime.setSecond(k);
	myTime.setTime(o,m,p);
	myTime.showTime();
}

