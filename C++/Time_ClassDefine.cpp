// 2019.3.4
// Time��Ķ���
/* ���һ��ʱ����Time��˽�����ݳ�Ա��hour(ʱ)��minute(��)��second(��)�� 
���г�Ա�����У�setHour(int)�������ݳ�Աhour��ֵ������12Сʱ�ƣ����Ƿ�������Ĭ��Ϊ12��
setMinue(int)�������ݳ�Աminute��ֵ���Ƿ�����Ĭ��Ϊ0��
setSecond(int)�������ݳ�Աsecond��ֵ���Ƿ�����Ĭ��Ϊ0��
setTime(int��int��int)����ʱ���֡����������ݳ�Ա��ֵ��
 showTime()��ʾʱ������ֵ�� 
��������main()�е�����Ӧ��Ա������ʹ��ʱ������ֵ�ܴӼ��̽��գ�����ȷ��ʾ��
��ʾ��ʱ���֡������2λ��ֵ��ʽ��ʾ �� */
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

