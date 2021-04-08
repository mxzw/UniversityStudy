#include <stdio.h>
#include <stdlib.h>

void PrintArray(int* a, int n)    
{    
    for (int i = 0; i < n; ++i)    
    {    
        printf("%d ", a[i]);    

    }            
    printf("\n");    

}     

//归并排序---升序
//首先将整个数组分成两个区间，然后再在这两个区间中进行归并排序，再向下划分，直到区间中只有一个数为止就结束划分
//然后再对当前区间进行排序，将区间中小的部分放入临时数组中，直到该区间全部放入临时数组为止，然后将该临时数组返回原来的数组
//这样就完成了对一个区间的排序,这样递归的向后走，直到数组中的元素全部有序
//其实这种思想，相当于一种后序遍历，先处理左右节点，然后再处理根节点 
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
    //该指针初始值为左区间，因为要存入临时数组的是该区间的值
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

//归并排序非递归实现
//我们可以采用循环的方法来代替归并排序递归中不断递归划分左右区间，然后再排序左右区间
//既然使用非递归，我们就可以由底向上进行归并
//即首先，先将数组中，紧挨着的两个元素进行排序，得到一个有序的两个元素的集合，继续向后走，可以得到n/2个有序的集合(11归并)
//然后再排序紧挨着的四个元素(22归并)，过程同上
//即每次都将紧挨着的gap个元素进行排序，然后走完后，gap每次都乘以2，直到gap大于等于n即可

void MergeSortNonR(int* a,int n)
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

void MergeSort(int* a,int n)
{
    int* tmp = (int*) malloc(sizeof(int)*n);
    _MergeSort(a,0,n-1,tmp);

    PrintArray(a,n);
    free(tmp);
}

int main()
{
    int a[] = {6,9,7,5,3,8,2,1,4};
    //MergeSort(a,sizeof(a)/sizeof(int));
    MergeSortNonR(a,sizeof(a)/sizeof(int));
    PrintArray(a,sizeof(a)/sizeof(int));
    return 0;
}
