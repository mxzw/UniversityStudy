// 2019.3.4
// Time��Ͷ���
/*  ������Time��Time��3�����õ����ݳ�Աhour��min��sec�ֱ��ʾСʱ���֡��롣
��������main�ж���Time�����t1��
��������main������t1�ĸ����ݳ�Ա�ٲ���������ݳ�Ա�� */
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
