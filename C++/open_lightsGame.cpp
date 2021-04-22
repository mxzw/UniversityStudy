#include<iostream>
using namespace std;
int main()
{
	int j = 1;
	int n,m; // n Õ»µÆ   m ¸öÈË 
	cin >> n >> m;
	int x[n+1];
	while( j <= m ){
		if( j == 1 ){
			for( int i = 0;i < n + 1;++i )  {
	            x[i] = 0;
	        }
		}
	    else if( j == 2 ) {
	    	for( int i = 1;i < n + 1;i++ )
	    	{
	    		if( i % j == 0 ){
	    			x[i] = 1;
				}
			}
		}
		else{
			for( int i = j;i < n + 1;++i ){
				
				if( i % j == 0 ){
					if( x[i] == 0 ) {
						x[i] = 1;
					}
					else {
						x[i] = 0;
					} 
				}
			}
		}  
		++j;
	}
	for( int i = 1; i < n + 1  ;i++ )
	{
		if( x[i] == 1 )
		{
		cout << i << " ";
	    }
	    
	    if( x[i] == 0 ){
	    	cout << endl;
	    	cout << i << " " << "NO" << endl;
		}
}

	return 0;
}
