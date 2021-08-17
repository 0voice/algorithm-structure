#include <iostream>

using namespace std;

int cs,n,m;
int a[100];
void f(int t)
{
     int i,j;
     if(cs==m)
     {
         for(i=1;i<=m;i++)
         {
             cout<<a[i]<<" ";
         }
         cout<<endl;
         cs--;
     }
     else
     {
         for(i=1;i<=n;i++)
         {
             for(j=1;j<=cs;j++)
             {
                 if(a[j]==i)
                    break;
             }
             if(j>cs)
             {
                 cs++;
                 a[cs]=i;
                 f(i);
             }
         }
         cs--;
     }
}

int main()
{
     cout<<"Please enter the number of 'n' :";
     cin>>n;
     cout<<"Enter the number of elements to take out the arrangement 'm' :";
     cin>>m;
     cs=0;
     f(0);
     return 0;
}


