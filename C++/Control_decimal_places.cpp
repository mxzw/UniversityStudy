/*在C++中，是没有格式符的，我们可以通过使用setprecision()函数来实现这个需求。
想要使用setprecision()函数，必须包含头文件#include <iomanip>。使用方式如下：

cout << "a=" << setprecision(2) << a <<endl;
这时候，我们会发现，如果a的值为0.20001，输出的结果为a=0.2，后面第二位的0被省略了。
如果我们想要让它自动补0，需要在cout之前进行补0的定义。代码如下：

cout.setf(ios::fixed);
cout << "a=" <<fixed<< setprecision(2) << a <<endl; //输出a=0.20
这样，我们就可以得到0.20了。当然，如果想要关闭掉补0，只需要对fixed进行取消设置操作。
cout.unsetf(ios::fixed);
cout << "a=" << setprecision(2) << a <<endl; //输出a=0.2
我们的输出结果就又变回a=0.2了。*/ 

