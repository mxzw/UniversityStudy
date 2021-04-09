#include<stdio.h>
#include<stdlib.h>  
#include<string.h>

void PrintArray(int* a, int n)                                                          
{                                               
    for (int i = 0; i < n; ++i)                                                                                              
    {                                             
            printf("%d ", a[i]);                                                               
                                                                             
        }                               
    printf("\n");    
                                                          
}

//计数排序
//顾名思义，就是对原数组中的每个元素进行计数，在临时数组中保存他们的对应的个数，然后再将其覆盖掉即可
void countSort(int* a,int n)
{
    //每次找到最大值和最小值，用来求出该数组的数值的范围
    int min = a[0],max = a[0];
    for(int i = 0;i < n;i++)
    {
        if(a[i]<min)
        {
            min = a[i];
        }
        if(a[i]>max)
        {
            max = a[i];
        }
    }
    //求出数组对于的范围
    int range = max - min + 1;
    //首先需要创建出range大小的数组
    int* countArr = (int*) malloc(sizeof(int)*range);
    //其次还要对其进行初始化，全部初始化为0
    memset(countArr,0,sizeof(int)*range);

    //统计次数
    for(int i = 0;i < n;i++)
    {
        //对所在位置进行计数
        countArr[a[i]-min]++;
    }

    //排序
    int k = 0;
    for(int i = 0;i < range; ++i)
    {

        //要将countArr中的值不一定就是1，可能有相等的数，countArr中的值就会大于1
        while(countArr[i]--)
        {
            a[k++] = i+min;
        }

    }
    free(countArr);
}

int main()    {  
    int a[] = {6,9,7,5,3,8,2,1,4};    
    countSort(a,sizeof(a)/sizeof(int));                              
    PrintArray(a,sizeof(a)/sizeof(int));               
    return 0;    
}   
