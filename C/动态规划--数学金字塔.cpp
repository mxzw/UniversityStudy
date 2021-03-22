#include<iostream>
#include<cstring>
using namespace std;

int dp_opt( int a,int x[][100] );
int main()
{
	int n;
	cin >> n;
	int p[100][100];
	memset(p,0,sizeof(p));
		for( int i = 0;i < n;i++ )
	{
		for(int j = 0;j <= i;j++)
		{
			
			cin >> p[i][j];
		}
	}
	int j = dp_opt( n,p );
	cout << j;
	return 0;
}
int dp_opt( int a,int x[][100] ){
	int *opt = new int[a];
	memset( opt,0,sizeof(opt) );
	for( int i = 0;i < a;i++ )
	{
		opt[i] = x[a-1][i];
	}
	for( int i = a-2; i >= 0;i-- ){
		for( int j = 0;j <= i;j++ ){
			opt[j] = x[i][j] + max( opt[j],opt[j+1] );
		}
	}	
	return opt[0];
}
/* 
#include<iostream>
#include<cstring>
#define MAXN 1000
using namespace std;
int a[MAXN+10][MAXN+10];
int f[MAXN+10];
int main()
{
	memset(a,0,sizeof(a));
	memset(f,0,sizeof(f));
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>a[i][j];
		}
	}
//	f=a[n];
    for(int i=1;i<=n;i++)
    {
    	f[i]=a[n][i];
    }
	for(int i=n-1;i>=1;i--)
	{
		for(int j=1;j<=i;j++)
		{
			f[j]=a[i][j]+max(f[j],f[j+1]);
		}
	}
	cout<<f[1]<<endl;
	return 0;
	} 
*/ 
 /*
#include<iostream>
#include<cstring>
using namespace std;
int f[1010][1010];//f[i][j]从第i行第j个数到最后一行的最大数字和 
int a[1010][1010];
int main()
{
	memset(a,0,sizeof(a));
	memset(f,0,sizeof(f));
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)//初始状态 
	{
		f[n][i]=a[n][i];
	}
	for(int i=n;i>=1;i--)//i个阶段 
	{
		for(int j=1;j<=i;j++)//j个状态 
		{
			f[i][j]=a[i][j]+max(f[i+1][j],f[i+1][j+1]);//取两个方向的最大数字和 
		}
	}
	cout<<f[1][1]<<endl;
	return 0;
} 
*/
