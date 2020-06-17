#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define  MAX_NUMBER 100000
using namespace std;
typedef struct node
{
 int m_nkey;
 node * m_pnext;
};
void bin_sort(int * a,int size,int bucket_size)
{
 node ** node_table=new node*[bucket_size];
 for (int i=0;i<bucket_size;i++)
 {
  node_table[i]=new node;
  node_table[i]->m_nkey=0;
  node_table[i]->m_pnext=NULL;
 }
 for (int i=0;i<size;i++)
 {
  node *pNode=new node;
  pNode->m_nkey=a[i];
  pNode->m_pnext=NULL;
  int index=a[i]/bucket_size;
  if (node_table[index]->m_nkey==0)
  {
   node_table[index]->m_nkey++;
   node_table[index]->m_pnext=pNode;
  }
  else
  {
   node *pTmep=node_table[index]->m_pnext;
   while(pTmep->m_pnext!=NULL&&pTmep->m_pnext->m_nkey<a[i])
    pTmep=pTmep->m_pnext;
  node *pNext=pTmep->m_pnext;//插入
  pTmep->m_pnext=pNode;
  pNode->m_pnext=pNext;
  node_table[index]->m_nkey++;
  }
 }
 for (int i=0;i<bucket_size;i++)
 {
  node *p=node_table[i]->m_pnext;
  while(p!=NULL)
  {
   cout<<p->m_nkey<<" ";
   p=p->m_pnext; 
  }
 }
for (int i=0;i<bucket_size;i++)
{
 node *p=node_table[i]->m_pnext;
 while(p!=NULL)
 {
  node *next=p->m_pnext;
  delete p;
  p=next;
 }
 p=NULL;
}
}
int main()
{
 ofstream out("test.txt",ofstream::out|ofstream::app);
 
 srand(time(NULL));
 for (int i=0;i<100000000;i++)
 {
  int a=rand()%100000;
  out<<a<<" ";
 }
 int a[MAX_NUMBER]={0};
 ifstream in("test.txt",ofstream::in);
 for (int i=0;i<MAX_NUMBER;i++)
 {
  in>>a[i];
 }
 bin_sort(a,MAX_NUMBER,1000);
 return 0;
}
