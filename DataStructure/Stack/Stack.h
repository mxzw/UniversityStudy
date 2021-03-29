#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int STDataType;

typedef struct Stack
{
    int *a;
    int top; //栈顶
    int capacity; //容量
}Stack;

void StackInit(Stack* pst);
void StackDestory(Stack* pst);
void StackPush(Stack* pst,STDataType x);
void StackPop(Stack* pst);
int StackSize(Stack* pst);
STDataType StackTop(Stack* pst);

//NULL返回1，非空返回0
int StackEmpty(Stack* pst);
