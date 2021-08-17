#include <cmath> 
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 10010
#define eps 1e-8
#define pro 0.97

using namespace std;
int n;
struct Point
{
    double x,y;
    friend ostream& operator << (ostream &_,Point a)
    {
        printf("%.3lf %.3lf\n",a.x,a.y);
        return _;
    } 
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
    Point operator + (const Point &a)
    {return Point(x+a.x,y+a.y);}
    Point operator - (const Point &a)
    {return Point(x-a.x,y-a.y);}
    Point operator * (double rate)
    {return Point(x*rate,y*rate);} 
    double operator * (const Point &a)
    {return x*a.x+y*a.y;}
};
struct GTY
{
    Point p;
    double g;
    friend istream& operator >> (istream &_,GTY &a)
    {
        scanf("%lf%lf%lf",&a.p.x,&a.p.y,&a.g);
        return _;
    }
}pt[N];
double Get_Dis(Point a,Point b)
{
    return sqrt((a-b)*(a-b)); 
}
Point Get_Direction(Point a)
{
    Point p(0,0);
    for(int i=1;i<=n;i++)
    {
        Point tmp=(pt[i].p-a)*(pt[i].g/Get_Dis(pt[i].p,a));
        p=p+tmp;
    }
    return p;
}
Point Climb_Hill(Point now,double basement)
{
    if(basement<eps)return now;
    Point to=Get_Direction(now);
    to=to*basement;
    return Climb_Hill(now+to,basement*pro);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)cin>>pt[i];
    Point Base_Point(1999.5,329.5);
    Point ans=Climb_Hill(Base_Point,100000);
    cout<<ans;
}
