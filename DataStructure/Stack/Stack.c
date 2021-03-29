#include "Stack.h"

void StackInit(Stack* pst)
{   
    assert(pst);

    pst->a = (STDataType*)malloc(sizeof(STDataType)*4);
    pst->top = 0;
    pst->capacity = 4;
}
void StackDestory(Stack* pst)
{
    assert(pst);
    free(pst->a);
    pst->a = NULL;
    pst->top = pst->capacity = 0;
}
void StackPush(Stack* pst,STDataType x)
{
    assert(pst);
    //说明栈已经满了
    if(pst->capacity == pst->top){
        STDataType* tmp =(STDataType*) realloc(pst,pst->capacity*2*sizeof(STDataType));
        if(tmp == NULL)
        {
            StackDestory(pst);
            exit(-1);
        }
        pst->capacity *= 2;
        pst->a = tmp;
    }
    pst->a[pst->top] = x;
    pst->top++;
}
void StackPop(Stack* pst)
{
    assert(pst);
    assert(!StackEmpty(pst));
    --pst->top;
}
int StackSize(Stack* pst)
{
    assert(pst);
    return pst->top;
}

STDataType StackTop(Stack* pst)
{
    assert(pst);
    assert(!StackEmpty(pst));

    return pst->a[pst->top - 1];
}

//NULL返回1，非空返回0
int StackEmpty(Stack* pst)
{
    assert(pst);
    return pst->top ==  0 ? 1 : 0;
}
