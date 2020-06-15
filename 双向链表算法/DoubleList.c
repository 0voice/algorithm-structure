
/*
* 双向链表
*/

#include "DoubleList.h"
#include "string.h"
#include<stdlib.h>


// 初始化链表
static void vListInit(DoubleListHandle_t pxList) 
{
  pxList->pxHead = NULL;
  pxList->pxTail = NULL;
}

static DoubleNodeHandle_t xListGetHeadNode(DoubleListHandle_t pxList) 
{
  return pxList->pxHead;
}

static DoubleNodeHandle_t xListGetTailNode(DoubleListHandle_t pxList) 
{
	return pxList->pxTail;
}

static DoubleNodeHandle_t xListGetPrevNode(DoubleNodeHandle_t pxNode) 
{
	return pxNode->pxPrev;
}

static DoubleNodeHandle_t xListGetNextNode(DoubleNodeHandle_t pxNode) 
{
	return pxNode->pxNext;
}

DoubleListHandle_t	xDoubleListGenericCreate(void)
{
	DoubleListHandle_t pxDoubleList = (DoubleListHandle_t)malloc(sizeof(DoubleList_t));	
	if(pxDoubleList != NULL)
	{
		vListInit(pxDoubleList);
	}
	return pxDoubleList;
}

static void vListPushToFront(DoubleListHandle_t pxList,DoubleNodeHandle_t pxNode) 
{
  pxNode->pxPrev  = NULL;
  pxNode->pxNext  = pxList->pxHead;
  if(pxList->pxHead)
  {
  	pxList->pxHead->pxPrev = pxNode;
  }
	else
  {
  	pxList->pxTail = pxNode;
  }
	pxList->pxHead = pxNode;
}

static void vListPushToBack(DoubleListHandle_t pxList,DoubleNodeHandle_t pxNode) 
{
  pxNode->pxNext  = NULL;
  pxNode->pxPrev  = pxList->pxTail;
  if(pxList->pxTail)
  {
  	pxList->pxTail->pxNext  = pxNode;
  }
	else
  {
  	pxList->pxHead  = pxNode;
  }
	pxList->pxTail  = pxNode;
}

static void vListInsertBefore(DoubleListHandle_t pxList,DoubleNodeHandle_t pxBefore,DoubleNodeHandle_t pxNode) 
{
  if(pxBefore) 
	{
    if(pxBefore->pxPrev)
    {
    	pxBefore->pxPrev->pxNext = pxNode;
    }
		else
    {
    	pxList->pxHead = pxNode;
    }
		pxNode->pxNext = pxBefore;
    pxNode->pxPrev = pxBefore->pxPrev;
    pxBefore->pxPrev = pxNode;
	} 
	else 
	{
	  vListPushToBack(pxList, pxNode);
	}
}

static void vListInsertAfter(DoubleListHandle_t pxList,DoubleNodeHandle_t pxAfter,DoubleNodeHandle_t pxNode) 
{
  if(pxAfter) 
	{
    if(pxAfter->pxNext)
    {
    	pxAfter->pxNext->pxPrev = pxNode;
    }
		else
    {
    	pxList->pxTail  = pxNode;
    }
		pxNode->pxPrev  = pxAfter;
    pxNode->pxNext  = pxAfter->pxNext;
    pxAfter->pxNext = pxNode;
	} 
	else 
	{
	  vListPushToFront(pxList, pxNode);
	}
}

static DoubleNodeHandle_t xListPopFromFront(DoubleListHandle_t pxList) 
{
	DoubleNodeHandle_t pxNode = NULL;
	
	if(pxList->pxHead) 
	{
		pxNode    = pxList->pxHead;
		if(pxList->pxHead->pxNext)
		{
			pxList->pxHead->pxNext->pxPrev = NULL;
		}
		else
		{
			pxList->pxTail  = NULL;
		}
		pxList->pxHead  = pxList->pxHead->pxNext;
		pxNode->pxPrev  = pxNode->pxNext = NULL;
		return pxNode;
	} 

	return NULL;

}

static DoubleNodeHandle_t xListPopFromBack(DoubleListHandle_t pxList) 
{
	DoubleNodeHandle_t pxNode = NULL;
	
  if(pxList->pxTail) 
	{
    pxNode = pxList->pxTail;
    if(pxList->pxTail->pxPrev)
    {
    	pxList->pxTail->pxPrev->pxNext  = NULL;
    }
		else
    {
    	pxList->pxHead  = NULL;
    }
		pxList->pxTail  = pxList->pxTail->pxPrev;
    pxNode->pxPrev  = pxNode->pxNext    = NULL;
    return pxNode;
  }
  return NULL;
}

static DoubleNodeHandle_t xListRemove(DoubleListHandle_t pxList,DoubleNodeHandle_t pxNode) 
{
  if(pxNode->pxPrev)
  {
  	pxNode->pxPrev->pxNext  = pxNode->pxNext;
  }
	else
  {
  	pxList->pxHead  = pxNode->pxNext;
  }
	if(pxNode->pxNext)
  {
  	pxNode->pxNext->pxPrev  = pxNode->pxPrev;
  }
	else
  {
  	pxList->pxTail  = pxNode->pxPrev;
  }
	return pxNode;
}

static unsigned char  eListIsEmpty(DoubleListHandle_t pxList) 
{
  if(pxList->pxHead || pxList->pxTail)
  {
  	return 0;
  }
  return 1;
}

static unsigned long ulListGetSize(DoubleListHandle_t pxList) 
{
  unsigned long lnSize = 0;
  DoubleNodeHandle_t pxNode    = xListGetHeadNode(pxList);
  while(pxNode) 
	{
    ++ lnSize;
    pxNode  = xListGetNextNode(pxNode);
  }
  return lnSize;
}

static DoubleListHandle_t xListCombine(DoubleListHandle_t pxList1,DoubleListHandle_t pxList2) 
{
  if(!eListIsEmpty(pxList2)) 
	{
    if(!eListIsEmpty(pxList1)) 
		{
        pxList1->pxTail->pxNext = pxList2->pxHead;
        pxList2->pxHead->pxPrev = pxList1->pxTail;
        pxList1->pxTail = pxList2->pxTail;
    } 
		else 
		{
        pxList1->pxHead = pxList2->pxHead;
        pxList1->pxTail = pxList2->pxTail;
    }
    pxList2->pxHead = pxList2->pxTail   = NULL;
  }
  return pxList1;
}

#if defined	DOUBLELIST_TEST
typedef struct MsgNodeDef 
{
    DECLARELISTNODE		
    int	iMsg;					
}xMSGNODE;
typedef xMSGNODE		MsgNode_t;
typedef MsgNode_t*	MsgNodeHandle_t;

DoubleListHandle_t	pxLstMsgQueue;
MsgNode_t						msg1,msg2;
MsgNodeHandle_t 		pxMsgNodeTmp = NULL;


#endif
