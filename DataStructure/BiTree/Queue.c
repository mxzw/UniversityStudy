#include "Queue.h"

//Queue.c

//初始化队列 

void QueueInit(Queue* q)

{

    q->front = q->tail = NULL;

}

// 队尾入队列                                                                                        

void QueuePush(Queue* q, QDataType data)   

{   

    assert(q);   



    QNode* newNode = (QNode*)malloc(sizeof(QNode));   

    newNode->data = data;   

    newNode->next = NULL;   

    if(newNode != NULL)   

    {   

        if(q->tail == NULL)   

        {   

            q->front = q->tail = newNode;   

        }   

        else   

        {   

            q->tail->next = newNode;   

            q->tail = newNode;   

        }   

    }   



} 

// 队头出队列 

void QueuePop(Queue* q)

{

    assert(q);

    assert(!QueueEmpty(q));



    //只有一个结点时

    if(q->front == q->tail)

    {

        free(q->front);

        q->front = q->tail = NULL;

    }

    else

    {



        QNode* cur = q->front->next;

        free(q->front);

        q->front = cur;

    }

}

// 获取队列头部元素 

QDataType QueueFront(Queue* q)

{

    assert(q);

    assert(!QueueEmpty(q));

    return q->front->data;

}

// 获取队列队尾元素 

QDataType QueueBack(Queue* q)

{



    assert(q);

    assert(!QueueEmpty(q));

    return q->tail->data;                                                                                  



}

// 获取队列中有效元素个数 

int QueueSize(Queue* q)

{

    assert(q);



    QNode* cur = q->front;

    int size = 0;

    while(cur)

    {

        size++;

        cur = cur->next;

    }

    return 0;

}

// 检测队列是否为空，如果为空返回非零结果，如果非空返回0 

int QueueEmpty(Queue* q)

{

    assert(q);



    return q->front == NULL ? 1 : 0;

}

// 销毁队列 

void QueueDestroy(Queue* q)

{

    assert(q);

    QNode* cur = q->front;

    while(cur)

    {

        QNode* next = cur->next;

        free(cur);

        cur=next;

    }



    q->front = q->tail = NULL;



}   
