#include<iostream>
#include<cstring>

using namespace std;

int main()
{
	char a1[100],b1[100];
	int a[100],b[100],c[200];
	int lena,lenb,lenc;
	memset( a,0,sizeof(a) );
	memset( b,0,sizeof(b) );
	memset( c,0,sizeof(c) );
	cin >> a1;
	cin >> b1;
	lena = strlen( a1 ); // 不包括'\0'; 计算的是实际长度a 
	lenb = strlen( b1 );
	for( int i = 0;i <= lena-1; i++ ) {
		a[lena-i] = a1[i] - 48; 
		//根据ASCLL，字符数组内的数字要转化为实际的数字，就要减去48.  '0'的ASCLL也是48。 
	}
	for( int i = 0;i <= lenb-1;i++ ){
		b[lenb-i] = b1[i] - 48;
	}
	int x = 0;
	for( int i = 1; i <= lena;i++ )
	{
		x = 0;
		for( int j = 1; j <= lenb; j++ ){
			c[i+j-1] = a[i]*b[j] + x + c[i+j-1];
			x = c[i+j-1] / 10;
			c[i+j-1] %= 10;
		}
		c[i+lenb] = x; // 进位 
	}
	lenc = lena + lenb;
	while( c[lenc] == 0 &&  lenc > 1 ){
		lenc--;
	}
	for(int i = lenc;i >=1 ; i-- )
	{
		cout << c[i];
	}
	return 0;
}

/*
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int main()
{
    char a1[100],b1[100];
    int a[100],b[100],c[100],lena,lenb,lenc,i,j,x;
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    gets(a1);gets(b1);
    lena=strlen(a1);lenb=strlen(b1);
    for (i=0;i<=lena-1;i++) a[lena-i]=a1[i]-48;
    for (i=0;i<=lenb-1;i++) b[lenb-i]=b1[i]-48;
    for (i=1;i<=lena;i++)
    {
         x=0;                                     
         for (j=1;j<=lenb;j++)                 
         {
                     c[i+j-1]=a[i]*b[j]+x+c[i+j-1];    
                     x=c[i+j-1]/10;
           c[i+j-1] %= 10;
         }
         c[i+lenb]=x;                               
    }
    lenc=lena+lenb;
    while (c[lenc]==0&&lenc>1)      
        lenc--;
    for (i=lenc;i>=1;i--)
        cout<<c[i];
    cout<<endl;
    return 0;
}
*/
