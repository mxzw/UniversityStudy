#include<stdio.h>

void swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//向下调整算法
void adjustDown(int* a,int n,int parent)
{
    int root = parent;
    //升序，建大堆
    //定义左孩子,右孩子+1即可
    int child = root * 2 + 1;
    while(child < n)
    {
        if(child + 1 < n && a[child + 1] > a[child])
        {
            child++;
        }
        if(a[child] > a[root])
        {
           swap(&a[child],&a[root]);

           root = child;
           child = root*2 + 1;
        }
        else
        {
            break;
        }
    }

}

//堆排序
void heapSort(int* a,int n)
{
    //建堆
    for(int i = ((n - 1) - 1) / 2 ; i >= 0; i--)
    {
        adjustDown(a,n,i);
    }

    int end = n - 1;
    while(end > 0)
    {
        swap(&a[0],&a[end]);

        //adjust中while循环是小于n的，所以不会将end对应的值算入的
        adjustDown(a,end,0);
        end--;
    }

}

int main()
{
    int a[] = {1,6,3,5,8,5};
    heapSort(a,(int)(sizeof(a)/sizeof(int)));
    for(int i = 0; i < (int)(sizeof(a)/sizeof(int));i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
