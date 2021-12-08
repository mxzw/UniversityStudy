#include <iostream>

using namespace std;

int main()
{
    int i = 1;
    printf("%d,%d",i++,i++);
    // ++i ,++i ==> 3,3
    // ++i, i++ ==> 3,1
    // i++, ++i ==> 2,3
    // i++, i++ ==> 2,1

    //const int a = 10;
    //int *p = (int *)(&a);
    //*p = 20;

    //cout << "a = "  << a << ",p = " << *p << endl;
    //return 0;
}
