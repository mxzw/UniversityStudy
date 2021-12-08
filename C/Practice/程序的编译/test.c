#include<stdio.h>

//要实现num的奇数位和偶数位互换，可以先用 & 操作符将奇数位和偶数位均取出来
//num & 0101 0101 ...（奇数位为1）得该num的奇数位，再左移一位可变为偶数
//num & 1010 1010 ...（偶数位为1）得该num的偶数位，再右移一位可变为奇数
//之后再取两个结果的 | 操作，即可保持原num的数位不变 
#define ExchangeNum(num) ((((num) & 0x55555555)<<1) | (((num) & 0xaaaaaaaa)>>1))

int main()
{	
  printf("原num为156\n");
  printf("交换后的num为%d\n",ExchangeNum(156));
  return 0;
}
