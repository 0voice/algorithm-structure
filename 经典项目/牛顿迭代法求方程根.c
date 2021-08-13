//编写用牛顿迭代法求方程根的函数。方程为，系数a、b、c、d由主函数输入。求x在1附近的一个实根。求出根后，由主函数输出。

//牛顿迭代法的公式是：，设迭代到  时结束。


#include<stdio.h>
#include<math.h>

int main()
{
    /*函数功能是用牛顿迭代法求方程的根*/
    float solution( float a, float b, float c, float d);
    float a, b, c, d, x;  /*a,b,c,d代表所求方程的系数，x用来记录求得的方程根*/
    printf("请输入方程的系数：");
    scanf("%f %f %f %f", &a, &b, &c, &d);
    x = solution(a, b, c, d);
    printf("所求方程的根为x=%f", x);

    return 0;
}

float solution(float a, float b, float c, float d)
{
    float x0, x=1.5, f, fd, h;  /*f用来描述方程的值，fd用来描述方程求导之后的值*/
    do
    {
        x0 = x;  /*用所求得的x的值代替x0原来的值*/
        f = a*x0*x0*x0 + b*x0*x0 + c*x0 + d;
        fd = 3*a*x0*x0 + 2*b*x0 + c;
        h = f / fd;
        x = x0 - h;  /*求得更接近方程根的x的值*/
    }
    while(fabs(x-x0) >= 1e-5);

    return x;
}

//运行结果：

//请输入方程的系数：2 -3 4 -2
//所求方程的根为x=0.694146
