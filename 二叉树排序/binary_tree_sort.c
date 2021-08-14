#include <stdio.h>
#include <malloc.h>

typedef struct node{
	int value;
	struct node *l;
	struct node  *r;
}NODE;
/*插入*/
NODE *sort(NODE *head, int d);
/*输出*/
void output(NODE *head);
/*初始化*/
NODE *createnode(int value);
void main()
{
	NODE *head = NULL;
	int d;
	/*0 作为输入的结束*/
	while(1)
	{
		scanf("%d", &d);
		if (!d)
			break;
		else
		{
			if ( head == NULL){
				head = createnode(d);
				continue;
			}
			else
				sort(head, d);
		}	
	}
	
	output(head);
}
NODE *sort(NODE *head, int d)
{
	NODE *p;
	p = head;
	
	if ((p->value > d) && (p->l == NULL)){
		p->l = createnode(d);
		return p;
	}
	if((p->value < d) && (p->r == NULL)){
		p->r = createnode(d);
		return p;
	}
	if (p->value == d)
		return p;
	if(p->value > d)
		p = sort(p->l, d);
	else
		p = sort(p->r, d);	
	
}
NODE *createnode(int d)
{
	NODE *p;
	p = (NODE*)malloc(sizeof(NODE));
	p->value = d;
	p->l = NULL;
	p->r = NULL;
	return p;
}
/*中顺输出*/
void output(NODE *head)
{
    NODE *p; 
    p = head;
    if (head == NULL )
        return;
    output(p->l);
    printf("%-5d", p->value);
    output(p->r);
}
