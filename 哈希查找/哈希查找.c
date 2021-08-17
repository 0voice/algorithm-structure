#include<stdio.h>
#include<stdlib.h>
 
#define tablesize 5
typedef int ElemType;  
typedef struct HashNode  
{  
	ElemType elem;  
	struct HashNode *next;  
}HashNode;  
 
 
typedef struct  
{  
	HashNode ChainHash[tablesize];  
	int  count;  
}HashTable;  
 
 
int hash_mod(ElemType key)  
{  
	return key % tablesize;  
}  
 
 
void InsertHash(HashTable *h, int key)  
{  
	HashNode *p;  
	int index;  
	p = (HashNode*)malloc(sizeof(HashNode));  
	p->elem = key;  
	index = hash_mod(key);  
	p->next = h->ChainHash[index].next;  
	h->ChainHash[index].next = p;  
	h->count++;  
}  
 
 
void CreateHashTable(HashTable *h, int n)  
{  
	int key;  
	int i;  
	for(i = 0; i < n; i++)  
	{  
		printf("Input the  %d key :", i+1);  
		scanf_s("%d", &key);  
		InsertHash(h, key);  
	}	
}  
 
 
void PrintHashTable(HashTable *h)  
{  
	int i;  
	HashNode *p;  
	for(i = 0;i <= tablesize; i++)  
	{  
		p = h->ChainHash[i].next;  
		while(p)  
		{  
			printf("%-5d", p->elem);  
			p = p->next;  
		}  
	}  
}  
 
 
int SearchHash(HashTable *h, int key)  
{  
	HashNode *p;  
	int index;  
	int counter = 0;  
	index = hash_mod(key);  
	p = h->ChainHash[index].next;  
	while(p)  
	{  
		if(p->elem == key)  
			return 1;  
		else   
			p = p->next;  
	}  
	return 0;  
}  
