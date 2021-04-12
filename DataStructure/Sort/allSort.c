#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//打印数组
void PrintArray(int* a, int n)                                                          
{                                               
    for (int i = 0; i < n; ++i)                                                                                              
    {                                             
        printf("%d ", a[i]);                                                               

    }                               
    printf("\n");    

}  

//交换
void swap(int* a,int* b)    
{    
    int tmp = *a;    
    *a = *b;    
    *b = tmp;    
}    

//冒泡排序
void BubbleSort(int* a,int n)    
{    
    int end = n;    
    while(end > 0)                                                                                                                                                      
    {    
        //一趟冒泡排序
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

//插入排序
void InsertSort(int* a,int n)
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

// 希尔排序
void ShellSort(int* a, int n)
{
    //进行多趟预排序，然后再进行插入排序        
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



// 选择排序
void SelectSort(int* a, int n)
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

// 堆排序
void AdjustDown(int* a, int n, int parent)
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
void HeapSort(int* a, int n)
{
    //建堆
    for(int i = ((n - 1) - 1) / 2 ; i >= 0; i--)
    {
        AdjustDown(a,n,i);
    }

    int end = n - 1;
    while(end > 0)
    {
        swap(&a[0],&a[end]);

        //adjust中while循环是小于n的，所以不会将end对应的值算入的
        AdjustDown(a,end,0);
        end--;
    }

}

int GetMidIndex(int* a, int begin, int end)
{
    int mid = begin + ((end - begin) >> 1);
    if (a[begin] < a[mid])
    {
        if (a[mid] < a[end])
        {
            return mid;

        }
        else if (a[begin] > a[end])
        {
            return begin;

        }
        else
        {
            return end;

        }

    }
    else // begin >= mid
    {
        if (a[mid] > a[end])
        {
            return mid;

        }
        else if (a[begin] < a[end])
        {
            return begin;

        }
        else
        {
            return end;

        }

    }


}

int PartSort1(int* a, int begin, int end)
{
    int midindex = GetMidIndex(a, begin, end);
    swap(&a[begin], &a[midindex]);

    int key = a[begin];
    int start = begin;
    /*
     *  这里要从右边走，如果从左边走，
     *      可能最后一步，如果找不到大于
     *          基准值的，会导致begin == end
     *              即相遇，但是右边还没有走，所以
     *                  这里的值一定大于基准值，最后交换
     *                      就会出问题，所以一定要从右边走，
     *                          即使最后一次找不到小于基准值的，
     *                              会和左边相遇，而左边此时还没走，
     *                                  一定比基准值小，最后交换肯定没有问题
     *                                      */
    while (begin < end)
    {
        // end 找小
        while (begin < end && a[end] >= key)
            --end;

        // begin找大
        while (begin < end && a[begin] <= key)
            ++begin;

        swap(&a[begin], &a[end]);

    }
    //最后的交换一定要保证a[begin] < a[start], 所以要从右边走
    swap(&a[begin], &a[start]);
    return begin;

}

int PartSort2(int* a, int begin, int end)
{
    //begin是坑
    int key = a[begin];
    while (begin < end)
    {
        while (begin < end && a[end] >= key)
            --end;

        // end给begin这个坑，end就变成了新的坑。
        a[begin] = a[end];

        while (begin < end && a[begin] <= key)
            ++begin;

        // end给begin这个坑，begin就变成了新的坑。
        a[end] = a[begin];
    }

    a[begin] = key;

    return begin;
}


/*
   前后指针法
   */
int PartSort3(int* a, int begin, int end)
{
    int midindex = GetMidIndex(a, begin, end);
    swap(&a[begin], &a[midindex]);

    int key = a[begin];
    int prev = begin;
    int cur = begin + 1;

    while (cur <= end)
    {
        // cur找小，把小的往前翻，大的往后翻
        if (a[cur] < key && ++prev != cur)
            swap(&a[cur], &a[prev]);

        ++cur;
    }

    swap(&a[begin], &a[prev]);

    return prev;
}

// []
void QuickSort(int* a, int left, int right)
{
    if (left >= right)
        return;

    if (right - left + 1 < 10)
    {
        InsertSort(a+left, right - left + 1);
    }
    else
    {
        int div = PartSort3(a, left, right);
        //[left, div-1]
        //[div+1, right]
        QuickSort(a, left, div - 1);
        QuickSort(a, div + 1, right);
    }
}
#include "Stack.c"
//用栈模拟递归，用队列也可以实现
void QuickSortNonR(int* a, int left, int right)
{
    Stack st;
    StackInit(&st);
    //先入大区间
    if (left < right)
    {
        StackPush(&st, right);
        StackPush(&st, left);
    }
    //栈不为空，说明还有没处理的区间
    while (StackEmpty(&st) != 0)
    {
        left = StackTop(&st);
        StackPop(&st);
        right = StackTop(&st);
        StackPop(&st);
        //快排单趟排序
        int div = PartSort1(a, left, right);
        // [left div-1]
        // 把大于1个数的区间继续入栈
        if (left < div - 1)
        {
            StackPush(&st, div - 1);
            StackPush(&st, left);
        }

        // [div+1, right]
        if (div+1 < right)
        {
            StackPush(&st, right);
            StackPush(&st, div + 1);
        }
    }

}

void _MergeSort(int* a,int left,int right,int* tmp)
{
    //返回的条件是当左右区间值相等时，表明该区间就只有一个节点 
    if(left == right)
    {
        return;
    }

    //这种求中值的方法，可以避免值溢出的可能性
    //试想，若mid = (left + right) >> 1 ，若left和right的值都大于整型范围的一半，则left+right就会发生值溢出的情况
    int mid = left + ((right-left) >> 1);

    //[left,mid] [mid+1,right]   
    _MergeSort(a,left,mid,tmp);
    _MergeSort(a,mid+1,right,tmp);

    //在处理完左右区间之后，进行排序
    //所谓排序，即是对比左右区间的元素，将较小的元素放入临时数组中，直到将两个区间的值全部存入，最后再将临时数组中的值更新到原数组中即可

    //首先保存两个区间的头尾指针
    int begin1 = left, end1 = mid;
    int begin2 = mid+1,end2 = right;

    //i为临时数组的指针，注意该指针要指向原数组的该元素的位置
    //���指针初始值为左区间，因为要存入临时数组的是该区间的值
    int i = left;

    //循环结束的条件肯定是将两个左右区间走完
    while(begin1 <= end1 && begin2 <= end2)
    {

        if(a[begin1] < a[begin2])
        {
            tmp[i++] = a[begin1++];
        }
        else
        {
            tmp[i++] = a[begin2++];

        }
    }

    //走到这,我们不知道到底是哪个区间先走完的
    //所以应该对两个区间都进行判断一下
    //首先经过递归后，左右区间都是有序的，所以只需将还有剩余元素的数组全部放入临时数组中即可

    while(begin1 <= end1)
    {
        tmp[i++] = a[begin1++];
    }

    while(begin2 <= end2)
    {
        tmp[i++] = a[begin2++];
    }

    //走到这里，已经将区间的所有值排好序放入临时数组中，现在只需将临时数组中的值放入原数组中就ok了

    int k = left;
    while(k <= right)
    {
        a[k] = tmp[k];
        k++;
    }


}


// 归并排序递归实现
void MergeSort(int* a, int n)
{
    int* tmp = (int*) malloc(sizeof(int)*n);    
    _MergeSort(a,0,n-1,tmp);    

    free(tmp);  
}
// 归并排序非递归实现
void MergeSortNonR(int* a, int n)
{

    //首先创建一个临时的数组，用来更新原数组，使其有序
    int* tmp = (int*)malloc(sizeof(int)*n);
    //首先令gap为1，进行11归并
    int gap = 1;
    while(gap < n)
    {
        //然后，对数组中，每个紧挨着gap个的元素进行排序
        //注意，这里i每次走的是2倍的gap步，一个gap为一个区间，一次走两个gap步，即一次走两个区间
        for(int i = 0; i < n; i += 2*gap)
        {
            //左区间为从i开始到i+gap-1的闭区间，右区间为从i+gap到i+2*gap-1的闭区间
            //即[i i+gap-1] [i+gap,i+2*gap-1]
            //解释：就是在该数组中划分多个左右区间，左区间就是i+gap个值，对应的右区间就是gap的二倍，gap走一步是左区间，走两步是右区间            

            //首先保存两个区间的头尾指针
            int begin1 = i, end1 = i+gap-1;
            int begin2 = i+gap,end2 = i+gap*2-1;

            //begin2和end2可能会存在数组越界的问题发生 （即右区间）

            //1.当数组不是整分的，即数组长度是奇数，或是在进行分区后，区的总数是个奇数，这种情况是begin2的值已经大于n了，即是有左区间，却不存在右区间
            if(begin2 >= n)
            {
                break;
            }

            //2.右区间是存在的，但是右区间中的值不够gap个,则将保留右区间。
            if(end2 >= n)
            {
                end2 = n - 1;
            }

            //i为临时数组的指针，注意该指针要指向原数组的该元素的位置
            //该指针初始值为左区间，因为要存入临时数组的是该区间的值
            int j =begin1;

            //循环结束的条件肯定是将两个左右区间走完
            while(begin1 <= end1 && begin2 <= end2)
            {

                if(a[begin1] < a[begin2])
                {
                    tmp[j++] = a[begin1++];
                }
                else
                {
                    tmp[j++] = a[begin2++];

                }
            }

            //走到这,我们不知道到底是哪个区间先走完的
            //所以应该对两个区间都进行判断一下
            //首先经过递归后，左右区间都是有序的，所以只需将还有剩余元素的数组全部放入临时数组中即可

            while(begin1 <= end1)
            {
                tmp[j++] = a[begin1++];
            }

            while(begin2 <= end2)
            {
                tmp[j++] = a[begin2++];
            }

            //走到这里，已经将区间的所有值排好序放入临时数组中，现在只需将临时数组中的值放入原数组中就ok了

            int k = i;
            //注意这里千万不写成i+gap*2-1，因为可能存在数组的越界访问
            while(k <= end2)
            {
                a[k] = tmp[k];
                k++;
            }

        }
        gap *= 2;
    }

    free(tmp);
}



// 计数排序
void CountSort(int* a, int n)
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




void testOP()
{
    srand(time(0));
    const int N = 100000;
    int* a1 = (int*)malloc(sizeof(int)*N);
    int* a2 = (int*)malloc(sizeof(int)*N);
    int* a3 = (int*)malloc(sizeof(int)*N);
    int* a4 = (int*)malloc(sizeof(int)*N);
    int* a5 = (int*)malloc(sizeof(int)*N);
    int* a6 = (int*)malloc(sizeof(int)*N);
    for (int i = 0; i < N; ++i)
    {
        a1[i] = rand();
        a2[i] = a1[i];
        a3[i] = a1[i];
        a4[i] = a1[i];
        a5[i] = a1[i];
        a6[i] = a1[i];

    }
    int begin1 = clock();
    InsertSort(a1, N);
    int end1 = clock();
    int begin2 = clock();
    ShellSort(a2, N);
    int end2 = clock();
    int begin3 = clock();
    SelectSort(a3, N);
    int end3 = clock();
    int begin4 = clock();
    HeapSort(a4, N);
    int end4 = clock();
    int begin5 = clock();
    QuickSort(a5, 0, N-1);
    int end5 = clock();
    int begin6 = clock();
    MergeSort(a6, N);
    int end6 = clock();
    printf("InsertSort:%d\n", end1 - begin1);
    printf("ShellSort:%d\n", end2 - begin2);
    printf("SelectSort:%d\n", end3 - begin3);
    printf("HeapSort:%d\n", end4 - begin4);
    printf("QuickSort:%d\n", end5 - begin5);
    printf("MergeSort:%d\n", end6 - begin6);
    free(a1);
    free(a2);
    free(a3);
    free(a4);
    free(a5);
    free(a6);
}

int main()
{
    testOP();
    return 0;
}

