#include <stdio.h>
int main ()
{
	int integer1, integer2, total;
	printf( "%s", "Enter two integer:\n" );
	scanf( "%d %d", &integer1, &integer2 );// ���Ҫֱ��Ҫ����������integer) ��ô scanf �е� %d һ��Ҫ�� ���� �� ���� &  ���ֻ����һ��%d ��ôϵͳֻ���ȡ��һ�� &�е���  
	
	total = integer1 + integer2;
	printf( "The total is %d", total );
}
