#include<iostream>
using namespace std;
int rec( int (* )[2],int  );

int main()
{

	int a[100][2];
	int b = 0;
	for( int i = 0;i < 100;i++ ){	
		for( int j = 0; j < 2 ;j++ ){
			if( cin.peek() == '\n' ) break;
			cin >> a[i][j];
			b++;
		}
	}
	if( b%2 != 0 ) {
		b = (b-1)/2;
	}
	else b = b/2;
	int l = rec( a,b+1 );
	cout << l << endl;
	
	return 0;
}

int rec( int (*x)[2] , int n ){
	int i = 0,j = 0;
	int c,w;
		c = 0;
		for( i = 0;i < n;i++ ){
			c = c + x[i][1];
		}
		if( x[i+1][j] < x[i+1][j+1] ){
			w = w + x[0][0];

			for( i = 1;i < n;i++ ){
				w = w + x[i][1];
			}
		}
		else{
			w = 0;
		for( i = 0;i < n;i++ ){
			w = w + x[i][0];
		}
		}
		if( c > w )   return c;
	    else  return w;
} 
