#include<stdio.h>

void swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void PrintArray(int* a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);

    }
    printf("\n");

}

//插入排序--升序    
void insertSort(int* a,int n)    
{

    for(int i = 0; i < n - 1; i++)    
    {    
        //一次插入排序    
        int end = i;    
        //一次插入排序的过程是将第end+1号元素插入到[0,.....,end]的区间后，并保持数组有序    
        int tmp = a[end+1];    

        //然后end指针向前走，若 tmp < a[end] ，则继续向前走，并将end位置的元素挪动到end+1的位置，当tmp > a[end]的时候，则证明找到了，并将其插入到该位置    
        while(end >= 0)    
        {    
            if(tmp < a[end])                                                                                                                                            
            {    
                a[end + 1] = a[end];    
                --end;    
            }    
            else    
            {    
                break;    
            }    
        }    
        a[end + 1] = tmp;    

    }    
}

//快排优化----三数取中选key法
//当数组中的元素是有序的时候，此时的快排的时间复杂度为O(n^2)
//即可能会出现[0,n-1]的情况，即单支的情况
//由于快速排序的key值是可以任意选的
//因此，当数组有序的时候，我们可以选择中间的元素作为key值，这样最坏的情况就变为最优的情况，但实际中，我们并不知道数组是否有序
//因此，就可以比较三个数的所对应元素的值，将处于三数中间的作为key值返回，进行快排即可
//三个数为begin，mid，end。
int getMidIndex(int* a,int left, int right)
{
    //首先求出mid的值
    int mid = (left + right) >> 1;
    //当left < mid时
    if(a[left] < a[mid])
    {
        //当mid < right 时，返回mid的值（位于中间）
        if(a[mid] < a[right])
        {
            return mid;
        }
        else if(a[right] < a[left])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
    else //left >= mid
    {
        if(a[mid] > a[right])
        {
            return mid;
        }
        else if(a[left] < a[right])
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}

//快排--升序
//左右指针法---hoare版本
void quickSortHoare(int* a,int begin, int end)
{
    if(begin >= end)
    {
        return;
    }
    //以三数取中选key为基准
    int mid = getMidIndex(a,begin,end);
    //将选出来的值每次都和left做交换，即可保证每次的key都在left的位置
    swap(&a[mid],&a[begin]);
    int left = begin,right = end;
    //一趟快速排序
    //以左指针为基准，则先找右指针
    int tmp = left;

    while(left < right)
    {
        //右指针找小
        while(left < right && a[right] >= a[tmp])
        {
            right--;
        }
        //左指针找大
        while(left < right && a[left] <= a[tmp])
        {
            left++;
        }

        //找到后直接互换左右指针的值
        swap(&a[left],&a[right]);
    }
    //当左右指针相等时，退出循环，并交换
    swap(&a[tmp],&a[left]);
    //由于此时的基准值已被交换到有序的地方，要再遍历基准值的左右，就需要改变tmp的位置，即变为left或right指针指向的位置
    tmp = left;
    //然后再遍历基准值的左右
    //即 [left,tmp - 1] tmp [tmp + 1,right]
    quickSortHoare(a,begin,tmp - 1);
    quickSortHoare(a,tmp + 1,end);
}

//快排---挖坑法
//将key的值保存下来，然后走左右指针
//左指针找到小，则填入右边的坑，右指针找到大，则填入左边的坑，最后在左右指针相等时，将key的值填入左指针的坑里
//因为当左右指针相遇时，才是循环退出的条件，然后再交换即可
void quickSortHole(int* a,int left,int right)
{
    if(left >= right)
    {
        return;
    }
    //首先用三数取中选出key的值
    int mid = getMidIndex( a,left,right);
    swap(&a[mid],&a[left]);

    int begin = left, end = right;
    //首先保存begin位置的key值
    int tmp = a[begin];
    while(begin < end)
    {
        //先走右指针，找比key值小的元素，找到后将其放入左指针所指的位置(填坑)
        while(begin < end && a[end] >= tmp)
        {
            --end;
        }
        a[begin] = a[end];


        //再走左指针，找比key大的元素，找到后将其放入右指针所指的位置
        while(begin < end && a[begin] <= tmp)
        {
            ++begin;
        }
        a[end] = a[begin];
    }
    //当左右指针相等时，则将tmp放入他们所指的位置
    int hole = begin;
    a[hole] = tmp;

    quickSortHole(a,left,hole - 1);
    quickSortHole(a,hole + 1,right);

}

//快排--前后指针法
//即定义两个前后指针，若从left开始，则选择right处的值作为key，反之就选left处的值作为key
// 后指针先走，找小，找到比key处值小的元素，然后++前指针,再交换两个指针的值，然后再走后指针
//
void quickSortDP(int*a ,int left,int right)
{
    int mid = getMidIndex(a,left,right);
    swap(&a[left],&a[mid]);

    if(left >= right)
    {
        return;
    }
    //快排优化----最小区间优化
    //当[left,right]的范围很小时，即数据量很小时，就直接使用插入排序，减少递归的次数（即相当于减少叶子节点的递归数目）
    if(right - left < 10)
    {
        //这里数组a的起始一定要从left位置开始
        insertSort(a+left,right-left+1);
        return;
    }

    int next = left;
    int prev = left - 1;
    int key = right;

    while(next != key)
    {
        if(a[next] < a[key] && ++prev != next)
        {
            swap(&a[next],&a[prev]);
        }
        ++next;
    }
    //当next走到key的位置时，prev的下一个刚好是大于key值的元素，只要对其进行交换，就可固定key值为有序时的位置
    swap(&a[key],&a[++prev]);
    key = prev;

    quickSortDP(a,left,key - 1);
    quickSortDP(a,key+1,right);
}

#include "Stack.h"
//快排--非递归
//回想前几个快排递归，都是给定一段区间，在该区间中进行递归，执行的是相同的代码
//那么快排的非递归也可以用这样的思想来实现，用栈来保存区间，然后在一个循环中循环多次，通过每次入栈新区间，来模拟递归的实现
//首先将想要进行排序的区间[left,right]入栈，注意入的时候是先入right，再入left，这样弹出的时候先弹出的是left
//然后再用上面三种办法中的其中一种的一趟快排算法，在走完一趟后，入栈新的区间，再走下一次循环
//循环结束的条件是当栈为空时就结束，为空就代表着区间已经走完了
void quickSortNonR(int* a,int left,int right)
{
    //首先，初始化一个栈
    Stack s;
    StackInit(&s);
    //然后入栈区间值[left,right]
    StackPush(&s,right);
    StackPush(&s,left);

    //在这里循环单趟快排
    while(!StackEmpty(&s))
    {
        //获取栈顶的值，然后再将其弹出
        int begin = StackTop(&s);
        StackPop(&s);
        int end = StackTop(&s);
        StackPop(&s);

    int next = begin;
    int prev = begin - 1;
    int key = end;


    while(next != key)
    {
        if(a[next] < a[key] && ++prev != next)
        {
            swap(&a[next],&a[prev]);
        }
        ++next;
    }
    //当next走到key的位置时，prev的下一个刚好是大于key值的元素，只要对其进行交换，就可固定key值为有序时的位置
    swap(&a[key],&a[++prev]);
    key = prev;


     //   //单趟快排
     //   int mid = getMidIndex(a,left1,right1);
     //   swap(&a[left1],&a[mid]);

     //   int begin = left1,end = right1;

     //   //首先保存begin位置的key值
     //   int tmp = a[begin];
     //   while(begin < end)
     //   {
     //       //先走右指针，找比key值小的元素，找到后将其放入左指针所指的位置(填坑)
     //       while(begin < end && a[end] >= tmp)
     //       {
     //           --end;
     //       }
     //       a[begin] = a[end];


     //       //再走左指针，找比key大的元素，找到后将其放入右指针所指的位置
     //       while(begin < end && a[begin] <= tmp)
     //       {
     //           ++begin;
     //       }
     //       a[end] = a[begin];
     //   }
     //   //当左右指针相等时，则将tmp放入他们所指的位置
     //   int hole = begin;
     //   a[hole] = tmp;

        //当key的值处于[begin，end]区间的时候，然后入栈两个子区间[begin,key-1]和[key+1,end]
        if(key + 1 < end)
        {
            StackPush(&s,end);
            StackPush(&s,key+1);
        }
        if(begin < key - 1)
        {
            StackPush(&s,key-1);
            StackPush(&s,begin);
        }


    }
    StackDestory(&s);

}


int main()
{
    int a[] = { 9, 4, 6, 3, 2, 7, 7, 9, 1, 4, 5, 8  };
    //  int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0  };
    //quickSortHoare(a, 0, sizeof(a) / sizeof(int) - 1);
    //quickSortHole(a,0,sizeof(a)/sizeof(int)-1);
    //quickSortDP(a,0,sizeof(a)/sizeof(int)-1);
    quickSortNonR(a,0,sizeof(a)/sizeof(int)-1);
    PrintArray(a, sizeof(a) / sizeof(int));
    return 0;
}
