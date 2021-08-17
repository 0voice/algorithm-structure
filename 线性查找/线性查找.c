
#include<iostream>
#include<conio>

int linearsearch(int[],int,int);
void BubbleSort(int[],int);

void main()
{
int n = 100;
a = new int[n];

int index,j,temp;
cout<<"Enter number (if you enter 0 , entering will be ended :n";
cin>>temp;
for(index=0 ; temp != 0 ; index++)
{
a[index] = temp;
cin>>temp;
}

BubbleSort(a,index);

cout<<"nTHE SORTED ARRAY IS:n";
for(i=0 ; i<index ; ++i)
cout<<a[i]<<endl;

cout<<"nEnter the key word:";
cin>>k;

int key = linearsearch(a,index,k);

for(j=key ; j<index ; ++j)
a[j] = a[j+1];

for(i=0 ; i<index-1 ; ++i)
cout<<a[i]<<endl;;

getch();
}


void BubbleSort(int a[100],int y)
{
int i,j,hold;
for(i=1;i<=y-1;++i)
for(j=0;j<y-i;++j)
if(a[j]>a[j+1])
{
hold=a[j];
a[j]=a[j+1];
a[j+1]=hold;
}
}


int linearsearch(int a[],int m,int k)
{
for(int i=0 ; i<m ; ++i)
if(a[i]==k)
return i;
return -1;

}
