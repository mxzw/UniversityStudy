#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char a1[100] , b1[100];
	int a[100],b[100],c[200];
	int lena,lenb,lenc;
	memset( a,0,sizeof(a) );
	memset( b,0,sizeof(b) );
	memset( c,0,sizeof(c) );
	cin >> a1;
	cin >> b1;
	lena = strlen(a1);
	lenb = strlen(b1);
	for( int i = 0;i <= lena-1;i++ ){
		a[lena-i] = a1[i] - 48;
	}
	for( int i = 0;i <= lenb-1;i++ ){
		b[lenb-i] = b1[i] - 48;
	}
	int y = (lena<lenb) ? lena : lenb;
	int x = 0;
	for( int i = 1;i <= y;i++ ){
		c[i] = a[i] + b[i]+ x;
		x = c[i] / 10;
		c[i] %= 10;
	}
	 lenc = (lena>lenb) ? lena : lenb;
	for( int i = y+1;i <= lenc;i++ ){
		if( lena < lenb ) {
			c[i] = b[i] + x;
			x = c[i] / 10;
			c[i] %= 10;
		}
		else  {
			c[i] = a[i] + x;
			x = c[i] / 10;
			c[i] %= 10;
	    }
}
    if( c[lenc] == 0 && lenc > 1 ){
    	++lenc;
    	c[lenc] = 1;
	}
	for( int i = lenc;i >= 1; i-- ){
		cout << c[i];
	}
	return 0;
}
