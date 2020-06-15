/*
* 单链表
*/


#include<stdio.h>
#include<malloc.h>
#include"LinkList.h"


typedef struct _TLinkList
{
	LinkListNode head;
	int length;
}TLinkList;

LinkList *LinkListInit()
{
	TLinkList *slist=(TLinkList*)malloc(sizeof(TLinkList));
	if(slist!=NULL)
	{
	slist->head.next=NULL;
	slist->length=0;
	}
	return slist;
	
}

int LinkListLength(LinkList *list)
{
	TLinkList *slist=(TLinkList*)list;
	int length=0;
	
	LinkListNode *r;
	r=slist->head.next;
	while(r!=NULL)
	{
		r=r->next;
		length++;	
	}
	return length;
	
	
	
}
Bool LinkListIsEmpty(LinkList *list)
{
	if(list==NULL)
	{
		printf("\n当前链表不存在\n");
		return False;	
	}
	else
	{
		if(!LinkListLength(list))
			return True;	
		else 
			return False;
	}
}

void LinkListClear(LinkList *list)
{
	TLinkList *slist=(TLinkList*)list;
	if(slist!=NULL)
	{
		slist->head.next=NULL;
		slist->length=0;		
	}
}

void LinkListDestory(LinkList *list)
{
	free(list);
}

LinkListNode*LinkListGet(LinkList *list,int pos)
{
	LinkListNode *ret=NULL;
	
	TLinkList *slist=(TLinkList*)list;
	
	int i=0;
	
	if((slist!=NULL)&&(pos>0)&&(pos<=LinkListLength(list)))
	{
		LinkListNode* currentNode=(LinkListNode*)slist;
		for(i=0;(i<pos);i++) 
		{
			currentNode=currentNode->next;
		}
		ret=currentNode->next;
	}
	
	return ret;
} 

void LinkListInsert(LinkList *list,LinkListNode *node,int pos)
{
	TLinkList *slist=(TLinkList*)list;
	int flag=((slist!=NULL)&&(node!=NULL)&&(pos>=0));
	int i=0;
	if(flag)
	{
		LinkListNode*currentNode=(LinkListNode*)slist;
		for(i=0;(i<pos)&&(currentNode->next!=NULL);i++)
		{
			currentNode=currentNode->next;
		}
		node->next=currentNode->next;
		currentNode->next=node;
		slist->length++;			
	}	
 	
}

LinkListNode* LinkListDelete(LinkList*list,int pos)
{
	TLinkList*slist=(TLinkList*)list; 
	LinkListNode *ret=NULL;
	LinkListNode*deleteNode=NULL;
	int i=0;
	if((slist!=NULL)&&(pos>=0)&&(pos<slist->length))
	{
		LinkListNode *currentNode=(LinkListNode*)slist;
		for(i=0;(i<pos)&&(currentNode->next!=NULL);i++)
		{
			currentNode=currentNode->next;
		}
		ret=currentNode->next;
		deleteNode=currentNode->next;
		currentNode->next=ret->next;
		
		slist->length--;
		free(deleteNode);
	} 
	return ret;
	
}