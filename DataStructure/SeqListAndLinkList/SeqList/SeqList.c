#include "SeqList.h"

void SeqListInit(seqList* s1 )
{
    assert(s1);
    s1->a = (SeqDataType*) malloc(sizeof(SeqDataType)*4);
    memset(s1->a,0,sizeof(SeqDataType)*4);
    if(s1->a  == NULL){
        printf("malloc fail\n");
        exit(-1);
    }
    s1->size = 0;
    s1->capacity = 4;
}
void SeqListDestroy(seqList* s1 )
{
    assert(s1);
    free(s1->a);
    s1->a = NULL;
    s1->size = s1->capacity = 0;
}

void SeqListPushBack(seqList* s1,SeqDataType x)
{
    assert(s1);

    //检查空间，不够了需要增容
    CheckCapacity(s1);

    s1->a[s1->size] = x;
    ++s1->size;
}
void SeqListPushFront(seqList* s1,SeqDataType x)
{
    assert(s1);
    CheckCapacity(s1);
    int end = s1->size-1;
    while(end >= 0)
    {
        s1->a[end+1] = s1->a[end];
        --end;
    }
    s1->a[0] = x;
    s1->size++;
}
void SeqListPopFront(seqList* s1)
{
    assert(s1);
    assert(s1->size > 0);
    //挪动数据
    int begin = 1;
    while(begin < s1->size)
    {
        s1->a[begin-1] = s1->a[begin];
        ++begin; 
    }
    s1->size--;
}
void SeqListPopBack(seqList* s1)
{
    assert(s1);
    assert(s1->size > 0);

    s1->size--;
}
void SeqListPrint(seqList* s1)
{
    int i = 0;
    for(; i < s1->size; ++i)
    {
        printf("%d ",s1->a[i]);
    }
    printf("\n");
}

void CheckCapacity(seqList* s1)
{
    //检查空间，不够了需要增容
    if(s1->size == s1->capacity)
    {
        SeqDataType* tmp = (SeqDataType* )realloc(s1->a,sizeof(SeqDataType)*s1->capacity*2);
        if(tmp == NULL){
            printf("malloc fail\n");
        }
        s1->a = tmp;
        s1->capacity *= 2;
    }
}

int SeqListFind(seqList* s,SeqDataType x)
{
    for(int i = 0;i < s->size; ++i)
    {
        if(s->a[i] == x)
        {
            return i;
        }
    }
    return -1;
}
void SeqListInsert(seqList* s1,int pos,SeqDataType x)
{
    assert(s1);
    assert(pos>=0 && pos <= size);

    CheckCapacity(s1);

    int end = s1->size - 1;
    //挪动数据
    while(end>=pos)
    {
        s1->a[end+1] = s1->a[end];
        --end;
    }

    s1->a[pos] = x;
    s1->size++;
}
void SeqListErase(seqList* s1,int pos)
{
    assert(s1);
    assert(pos >= 0 && pos <= s1->size);

    //挪动覆盖要删除位置的数据
    for(int i = pos + 1;i < s1->size; i++)
    {
        s1->a[i-1] = s1->a[i];

    }
    s1->size--;
}
