#include<stdio.h>

void swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
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



int main()
{
    int a[] = {2,2,4,5,3,8,5,1};
    insertSort(a,(int)(sizeof(a)/sizeof(int)));
    for(int i = 0;i < (int)(sizeof(a)/sizeof(int));i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
