#include<iostream>
#include<algorithm>
using  namespace std;

int rec_opt(int*, int);
int main()
{
	int a[100];
	int b = 0;
	for (int i = 0; i < 100; i++) {
		if (cin.peek() == '\n') break;
		cin >> a[i];
		b++;
	}
	int j = rec_opt(a, b-1);
	cout << j << endl;

	return 0;
}

int rec_opt(int *p, int n)
{
	if (n == 0) return p[0];
	if (n == 1) return (max(p[0], p[1]));
	int x = p[n] + rec_opt(p, n - 2);

	int y = rec_opt(p, n - 1);

	return(max(x, y));
}

