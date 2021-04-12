#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node * next;
}Node;


void DeleteNode(Node *s,Node *L)
{
	int i=0;
	Node *p,*q;
	p = L;
	q = L;
	while(p->next->next!=s)
	{
		p = p->next;
	}
	while(q->next!=s)
	{
		q = q->next;
		i++;
	}
	p->next = q->next;
	free(q);
	free(&L[i]); 
	/*
	Node *p,*q;
	p = s;
	while(p->next->next!=s)
	{
		p = p->next;
	}
	q = p->next;
	p->next = s;
	free(q);*/
}
void ShowNode( Node *L,int last )
{
	for(int i = 0;i < last;i++)
	{
		printf("%d ",L->data);
		L = L->next;
	}
	puts("");
}

/*
void DeleteLinkList(Node *L,Node *s)
{
	Node *h = L->next;
	Node *k = L;
	while(k->next!=s)
	{
		k = k->next;
	}
	while(h->next!=s)
	{
		h = h->next;
	}
	h = k->next;
	free(k);
	
}*/
/*
void CreateLinkList( Node *L )
{
	Node *a,*b,*c;
	int x;
	a = (Node*) malloc (sizeof(Node));
	c = (Node*) malloc (sizeof(Node));
	printf("输入需要删除前驱结点的s->data为："); 
	scanf("%d",a->data); 
	printf("输入链表的第一个值为：");
	scanf("%d",c->data);
	while((x=getchar())!= EOF)
	{
		b=(Node*)malloc(sizeof(Node));
		b->data = x;
		L->next = b;
		L = b;
	}
	L->next = c;
    DeleteLinkList(L,a);
    
}
*/

void InitNode(Node *n)
{
	n[0].data = 1;
	n[1].data = 3;
	n[2].data = 2;
	n[3].data = 7;
	n[4].data = 5;
	
	n[0].next = &n[1];
	n[1].next = &n[2];
	n[2].next = &n[3];
	n[3].next = &n[4];
	n[4].next = &n[1];
}


int main()
{	
	int a;
   	Node *s,*l;
	int n = 5;
	Node datanode[n];
	InitNode(datanode);
	ShowNode(datanode,n);
	printf("请输入要删除的结点：");
	 scanf("%d",&a);
	for(int i = 0;i < n;i++)
	{
		if( a==datanode[i].data )
		{
			s = &datanode[i];
		}
	 } 
	DeleteNode(s,datanode);
	ShowNode(datanode,n);
    return 0;
	}


/*	Node *n;
	int num=0,i=0;
	printf("请输入循环结点的个数：");
	scanf("%d",num);
	n = (Node*)malloc(sizeof(Node)*num);
	printf("输入循环结点的数值分别为："); 
	while(i < num);
	{
		scanf("%d",&n[i].data);

		n[i].next = &n[i+1];
		i++;
	}
	if(i==num)
	{
		n[i].next = &n[num-i];
	}
	DeleteNode(n,num);
	ShowNode(n,num);
	free(n);*/
	

