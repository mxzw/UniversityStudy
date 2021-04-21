// 2019.3.26
// const的例子
#include<iostream>
using namespace std;
int main()
{
	char p1 = 'X';
	cout << p1 << endl;
	
	char p2[] = "Hello World!";
	cout << p2 << endl;
	
	char *ptrp1;
	ptrp1 = &p1;
	cout << *ptrp1 << endl;
	ptrp1 = p2; /* 指针本身的值可以改变，可能指向变量p1的地址或数组p2的地址 */
	*ptrp1 = 'Y';/* 通过*ptrp1修改所指向单元的值 */ 
	cout << ptrp1 << endl;
	
	const char *p;
	p = &p1;
	cout << *p << endl;
	p = p2;
	//  若 *p = 'Z';
	/*  会编译错误，说明上面定义的 const char *p中的*p是常量， 
	   即 不允许通过该指针去修改指向单元的值  ---   p本身可以被改变
	    */
	cout << *p << endl;
	
	char const *pp;
	pp = &p1;
	cout << *pp << endl;
	pp = p2;
	// 若 *pp = ‘m'
	/* 会编译错误，说明上面定义的 char const *pp 中的 *pp 是常量
	   即 不允许通过该指针去修改指向单元的值 ---  pp本身可以被改变
	   所以 char const *pp 与 char const *pp 的效果相同 */ 
	cout << *pp << endl;
	const char *const ppp = &p1;
	// ppp = &p1 ---  出错
	cout << *ppp << endl;
	// ppp = p2 --- 出错
	// *ppp = 'M' --- 出错
	
	/* 因此，这种定义方法表示：该指针的取值不能改变，也就是不能指向其他的变量；
	   而且，该指针所指向的空间的值不能改变。 */ 
	return 0;
 } 
