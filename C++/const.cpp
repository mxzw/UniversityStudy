// 2019.3.26
// const������
#include<iostream>
using namespace std;
int main()
{
	char p1 = 'X';
	cout << p1 << endl;
	
	char p2[] = "Hello World!";
	cout << p2 << endl;
	
	char *ptrp1;
	ptrp1 = &p1;
	cout << *ptrp1 << endl;
	ptrp1 = p2; /* ָ�뱾���ֵ���Ըı䣬����ָ�����p1�ĵ�ַ������p2�ĵ�ַ */
	*ptrp1 = 'Y';/* ͨ��*ptrp1�޸���ָ��Ԫ��ֵ */ 
	cout << ptrp1 << endl;
	
	const char *p;
	p = &p1;
	cout << *p << endl;
	p = p2;
	//  �� *p = 'Z';
	/*  ��������˵�����涨��� const char *p�е�*p�ǳ����� 
	   �� ������ͨ����ָ��ȥ�޸�ָ��Ԫ��ֵ  ---   p������Ա��ı�
	    */
	cout << *p << endl;
	
	char const *pp;
	pp = &p1;
	cout << *pp << endl;
	pp = p2;
	// �� *pp = ��m'
	/* ��������˵�����涨��� char const *pp �е� *pp �ǳ���
	   �� ������ͨ����ָ��ȥ�޸�ָ��Ԫ��ֵ ---  pp������Ա��ı�
	   ���� char const *pp �� char const *pp ��Ч����ͬ */ 
	cout << *pp << endl;
	const char *const ppp = &p1;
	// ppp = &p1 ---  ����
	cout << *ppp << endl;
	// ppp = p2 --- ����
	// *ppp = 'M' --- ����
	
	/* ��ˣ����ֶ��巽����ʾ����ָ���ȡֵ���ܸı䣬Ҳ���ǲ���ָ�������ı�����
	   ���ң���ָ����ָ��Ŀռ��ֵ���ܸı䡣 */ 
	return 0;
 } 
