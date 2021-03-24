#include <stdio.h>
int main ()
{
	int integer1, integer2, total;
	printf( "%s", "Enter two integer:\n" );
	scanf( "%d %d", &integer1, &integer2 );// 如果要直接要两个整数（integer) 那么 scanf 中的 %d 一定要有 两个 和 两个 &  如果只输入一个%d 那么系统只会读取第一个 &中的数  
	
	total = integer1 + integer2;
	printf( "The total is %d", total );
}
