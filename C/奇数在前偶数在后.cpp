#include<stdio.h>
#define MAX 100 
typedef struct{
	int stu[MAX];
	int last;
}Node;

void CreateStu( Node *a )
{
	for(int i = 0;i<a->last;i++)
	{
		printf("请输入第%d个数组元素：",i);
		scanf("%d",&a->stu[i]);
	}
}

void ShowStu( Node *a )
{	
	printf("奇数在前偶数在后的排列结果为：");
	for(int i = 0;i < a->last;i++)
	{
		printf("%d",a->stu[i]);
	}
}

/*
typedef struct Node{
	int last;
	struct Node* next;
} Node,*LinkList; 

LinkList CreateLinkList( LinkList a )
{	
	a = (LinkList) malloc (sizeof(Node)); 
	a->next = NULL;
	Node *s;
	int k;
	printf("输入数组元素的个数: ");
	scanf("%d",&k);
	for( int i = 0; i < k;i++ )
	{
		s = (Node*) malloc (sizeof(Node));
		printf("第%d个数组元素为：",i);
		scanf("%d",&s->last);
		s->next = a->next;
		a->next = s;  
	}
	return a;

}

void outputLinkList( LinkList h )
{
	LinkList b = h;
	while(h->next!=NULL)
	{
		h = h->next;
		printf("%d ",h->last);
	}
}

*/
void SetStu( Node *a )
{
	int b[a->last];
	int j = 0;
	int i = 0;
	int t,n;
	for(int i = 0;i < a->last;i++ )
	{
		if(a->stu[i]%2==1)
		{
			b[j] = i;
			j++;

		}
	}
	n = j;
	j = 0;
	while(i < a->last)
	{
		t = a->stu[i];
	    a->stu[i]=a->stu[b[j]];
	    a->stu[b[j]]=t;
	    i++;
	    j++;
	    if(n==j)
	    {
	    	break;
		}
		
	}
	/*
		if(a->stu[i]%2==0)
		{
			while(j>=0){
			    if(a->stu[j]==0)
		    {
		    	j--;             // 1 2 3
			}
			    if(a->stu[j]==1)
			    {
			    	t = a->stu[i];
			    	a->stu[i]=a->stu[j];
			    	a->stu[j]= t;
			    	break;
				}
			}
			i++;
		}*/
}

int main()
{
	Node s;
	printf("请输入数组元素的个数：");
	scanf("%d",&s.last);
	CreateStu(&s);
	SetStu(&s);
	ShowStu(&s);
	return 0;
}
