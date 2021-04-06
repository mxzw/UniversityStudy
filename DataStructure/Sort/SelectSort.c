#include<stdio.h>

void PrintArray(int* a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);

    }
    printf("\n");

}


void swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//选择排序--升序
void selectSort(int* a,int n)
{
    //每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完 。
    int begin = 0;
    int end = n - 1;
    while(begin < end)
    {
        //mini 和 maxi每次存的是该数组的在[begin,...,end]区间的最小值和最大值
        int mini = begin,maxi = end;
        //筛选出当前区间的最小值下标和最大值下标
        for(int i = begin; i <= end; i++)
        {
            if(a[i] < a[mini])
            {
                mini = i;
            }
            if(a[i] > a[maxi])
            {
                maxi = i;
            }
        }
        //将筛选出来的最小值下标，存入begin的位置,begin从0开始，一直存放的是[begin,end]区间中的最小值
        swap(&a[begin],&a[mini]);
        //如果begin位置的元素是该区间最大的元素，由于前面的swap已经将begin的值换到mini所指的位置了，因此要将当前mini的下标给给maxi
        //这样才能将最大的值换到end的位置
        if(maxi == begin)
        {
            maxi = mini;
        }
        swap(&a[end],&a[maxi]);

        ++begin;
        --end;
    }
}
int main()
{
    int a[] = {6,5,1,3,4,8,9};
    selectSort(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
    return 0;

}
