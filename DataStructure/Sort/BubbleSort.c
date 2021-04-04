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

//冒泡排序---升序
void BubbleSort(int* a,int n)
{
    int end = n;
    while(end > 0)
    {
        //一次冒泡排序
        for(int i = 1; i < n; i++)
        {
            if(a[i] < a[i-1])
            {
                swap(&a[i],&a[i-1]);
            }
        }

        end--;

    }
}


int main()
{
    int a[] = {4,3,5,3,2,5};
    BubbleSort(a,6);
    PrintArray(a,6);
    return 0;
}
