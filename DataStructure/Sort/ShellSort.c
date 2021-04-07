#include<stdio.h>

void swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//希尔排序---升序
//进行多趟预排序，然后再进行插入排序
void shellSort(int* a,int n)
{
    //预排序的精华在于每次走的gap步，在逐渐的缩小，最终使数组接近于有序
    int gap = n;
    //当gap == 1的时候就会结束
    while(gap > 1)
    {
        //除以3是官方给的比较理想的除数
        gap = gap / 3 + 1;

        //单趟希尔排序
        //首先确定要走的gap步，对当前指针i和其i+gap对应的值做比较，如果i > i + gap ，则继续向后走(插入排序)，直到遇到比他小的值，若遇不到则放在最后位置上，然后指针i再后移，看下一个,这里用插入排序的思想比较好，用swap效率不够高
        //int gap= 10;
        // i 肯定只能走到 n - gap - 1的位置，在往后走gap的话，就会数组越界访问
        // i++，解决了每次只走每组gap步的烦恼(即 i += gap ,每次只走一组的gap，其他组的gap无法走)
        // 事实上这段代码就是插入排序的代码，只不过将1变为gap而已
        for(int i = 0; i < n - gap ; i++)
        {

            int end = i;
            int tmp = a[end + gap];
            //保存下一个gap步的值，用来做插入排序
            //即将 end + gap 的值往 [0,...,end]的区间插入，并保持其有序不变
            while(end >= 0)
            {
                if(tmp < a[end])
                {
                    a[end + gap] = a[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            a[end + gap] = tmp; 
        }

    }
}

int main()

{

    int a[] = {2,2,4,5,3,8,5,1};

    shellSort(a,(int)(sizeof(a)/sizeof(int)));

    for(int i = 0;i < (int)(sizeof(a)/sizeof(int));i++)

    {

        printf("%d ",a[i]);


    }

    printf("\n");

    return 0;


}    
