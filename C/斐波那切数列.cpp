#include<stdio.h>
int Fri( int );
int main()
{
	int n,m;
	scanf( "%d",&n );
	scanf( "%d",&m );
	int i = Fri(n);
	int j = Fri(m);
	printf( "%d\n",i );
	printf( "%d\n",j );
	return 0;
}
int Fri( int a ){
	if( a == 1 ) return 0;
	else if( a == 2 ) return 1;
	else return( Fri( a - 1 ) + Fri( a - 2 ) );
	
}
