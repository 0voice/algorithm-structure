#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<map>
#include<cstdlib>
#include<cmath>
#include<vector>
//#pragma comment(linker, "/STACK:1024000000,1024000000");
 
using namespace std;
 
#define INF 0x3f3f3f3f
 
double y;
 
double getsum(double x)
{
    return 6*pow(x,7)+8*pow(x,6)+7*pow(x,3)+5*x*x-y*x;
}
 
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf",&y);
        double delte=0.98;
        double t=100;
        double x=0;
        double ans=getsum(x);
        while(t>1e-8)
        {
            int flag=1;
            while(flag)
            {
                flag=0;
                double temp=x+t;
                if(temp>=0&&temp<=100&&getsum(temp)<ans&&fabs(ans-getsum(temp))>=1e-8)
                {
                    x=temp;
                    ans=getsum(temp);
                    flag=1;
                }
                temp=x-t;
                if(temp>=0&&temp<=100&&getsum(temp)<ans&&fabs(ans-getsum(temp))>=1e-8)
                {
                    x=temp;
                    ans=getsum(temp);
                    flag=1;
                }
            }
            t*=delte;
        }
        printf("%.4f\n",ans);
    }
    return 0;
}
