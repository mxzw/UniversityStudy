#include<iostream>
using namespace std;

int Add(int a, int b)
{
    cout << "test to overLoad (int Add)" << endl;
    return a + b;

}

void Add(double a, double b)
{
    cout << "test to overLoad (void Add)" << endl;

}


int main()
{
    cout << "test start!" << endl;
    int k = Add(1, 2);
    Add(1.1, 2.2);
    return 0;

}
