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


void main()  
{  
	int n ,key;  
	int i;  
	HashTable H;  
	printf("input the length of the Hash that we want to build:");  
	scanf_s("%d", &n);  
	for(i = 0;i <= tablesize; i++)  
		H.ChainHash[i].next = NULL;  
	H.count = 0;  
	CreateHashTable(&H,n);  
 
 
	printf("The hash table that we build is:");  
	PrintHashTable(&H);  
 
 
	printf("\nInput the key that we want to search(-1 for exit):");  
	scanf_s("%d", &key);  
	while(key != -1)  
	{  
		if(SearchHash(&H, key))  
			printf("There is a %d record in the Hash Table!\n", key);  
		else  
			printf("There is not a %d record in the Hash Table!\n", key);  
 
 
		printf("\nInput the key that we want to search(-1 for exit):");  
		scanf_s("%d", &key);  
	}  
 
	free(&H);
	return;
}  
