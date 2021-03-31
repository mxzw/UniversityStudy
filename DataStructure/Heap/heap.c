#include"heap.h"

//堆的创建
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
    hp->a = (HPDataType*) malloc(sizeof(HPDataType)*n);
    //如果申请失败则直接退出
    if(hp->a == NULL)
    {
        printf("Failed to malloc");
        exit(-1);
    }

    for(int i = 0; i < n; i++)
    {
        hp->a[i] = a[i];
    }

    for(int i = (n-2)/2;i >= 0; --i)
    {
        AdjustDown(hp->a,hp->size,i);

    }

    hp->size = n;
    hp->capacity = n;
}
// 堆的销毁
void HeapDestory(Heap* hp)
{
    assert(hp);
    free(hp->a);
    hp->a = NULL;
    hp->size = hp->capacity = 0;
}
// 堆的插入
void HeapPush(Heap* hp, HPDataType x)
{
    if(hp->size == hp->capacity)
    {
        HPDataType* tmp = (HPDataType*)realloc(hp->a,hp->capacity*2*sizeof(HPDataType));
        //若为空，则表示申请失败
        if(tmp == NULL)
        {
            printf("Failed to realloc");
            exit(-1);
        }
        hp->a = tmp;
        hp->capacity *= 2;
    }
    hp->a[hp->size] = x;
    hp->size++;
    //插入之后，需要进行向上调整算法，对堆进行调整
    AdjustUp(hp->a,hp->size - 1);
}
// 堆的删除
void HeapPop(Heap* hp)
{
    assert(hp);
    assert(hp->size > 0);
    //交换
    int tmp = hp->a[0];
    hp->a[0] = hp->a[hp->size - 1];
    hp->a[hp->size - 1] = tmp;

    --hp->size;
    AdjustDown(hp->a,hp->size,0);
}
// 取堆顶的数据
HPDataType HeapTop(Heap* hp)
{
    assert(hp);
    assert(hp->size > 0);

    return hp->a[0];

}
// 堆的数据个数
int HeapSize(Heap* hp)
{
    assert(hp);
    return hp->size;
}
// 堆的判空
int HeapEmpty(Heap* hp)
{
    assert(hp);
    return hp->size == 0 ? 1 : 0;
}

// 对数组进行堆排序
void HeapSort(int* a, int n)
{
    //升序要首先建立大堆
    //建堆的时间复杂度为o(N)
    for(int i = ((n - 1) - 1) / 2 ; i >= 0; i--)
    {
        AdjustDown(a,n,i);    
    }
    //每次选出剩余数中最大的数，并保存到每次最后的节点
    int end = n - 1;
    while(end > 0)
    {
        int tmp = a[end];
        a[end] = a[0];
        a[0] = tmp;

        //选出次小的数
        AdjustDown(a,end,0);
        --end;
    }
}

// TopK问题：找出N个数里面最大/最小的前K个问题。
// 比如：未央区排名前10的泡馍，西安交通大学王者荣耀排名前10的韩信，全国排名前10的李白。等等问题都是Topk问题，
// 需要注意：
// 找最大的前K个，建立K个数的小堆
// 找最小的前K个，建立K个数的大堆
void PrintTopK(int* a, int n, int k)
{
   //我们找最大的前k个数，首先先建一个小堆
   Heap hp;
   HeapCreate(&hp,a,k);
    //每次将a数组中其他的数与堆顶的元素做比较，如果大于，则则替换堆顶元素(所谓替换即先将堆顶元素删除，然后再插入该元素)
   for(int i = k;i < n;i++)
   {
       if(a[i] > HeapTop(&hp))
       {
           HeapPop(&hp);
           HeapPush(&hp,a[i]);
       }
   }

   for(int i = 0;i < k;i++)
   {
       printf("%d ",HeapTop(&hp));
       HeapPop(&hp);
   }
}

void TestTopk()
{
    int n = 10000;
    int* a = (int*)malloc(sizeof(int)*n);
    srand(time(0));
    //随机生成10000个数存入数组，保证元素都小于1000000
    for (int i = 0; i < n; ++i)
    {
        a[i] = rand() % 1000000;
    }
    //确定10个最大的数
    a[5] = 1000000 + 1;
    a[1231] = 1000000 + 2;
    a[531] = 1000000 + 3;
    a[5121] = 1000000 + 4;
    a[115] = 1000000 + 5;
    a[2335] = 1000000 + 6;
    a[9999] = 1000000 + 7;
    a[76] = 1000000 + 8;
    a[423] = 1000000 + 9;
    a[3144] = 1000000 + 10;

    PrintTopK(a, n, 10);
}

//向下调整算法
void AdjustDown(int* arr,int arrSize,int root)
{
    {
        int parent = root;
        //默认左右孩子中较小的节点为左孩子，由二叉树的性质可知，右孩子的位置就为child + 1
        int child = parent * 2 + 1;
        while(child < arrSize)
        {
            //首先得到左右孩子中较小的那一个
            if(child + 1 < arrSize && arr[child + 1 ] < arr[child])
            {
                ++child;    
            }

            //其次，比较较小孩子节点和父亲节点的大小，若小于，则交换，并且更新两个节点位置，若大于或等于，则break;
            if(arr[child] < arr[parent])
            {
                int tmp = arr[child];
                arr[child] = arr[parent];
                arr[parent] = tmp;

                parent =  child;
                child = parent * 2 + 1;
            }
            else
            {
                break;
            }
        }
    }
}

//向上调整算法
void AdjustUp(int* arr,int child)
{
    int parent = (child - 1) / 2;
    //当child等于0时，表明已经为根节点，证明整个已经排好序了，则退出
    //这里不能使用parent >= 0来做循环结束的标准，因为当child = 0时，parent = (child - 1) / 2 = -1 / 2 = 0。
    while(child > 0)
    {
        if(arr[child] < arr[parent])
        {
            int tmp = arr[child];
            arr[child] = arr[parent];
            arr[parent] = tmp;

            child = parent;
            parent = (child - 1) / 2;
        }
        else
        {
            break;
        }
    }
}
