#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 15
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
 
void createfib(void);               // 建立费氏数列
int findx(int);                     // 找x值
int fibsearch(int[], int);          // 费氏搜寻
void quicksort(int[], int, int);    // 快速排序
 
int Fib[MAX] = {-999};

//主程序（C/OC）

int main(void){

int number[MAX] = {0};
int i, find;
 
srand(time(NULL));
 
for(i = 1; i <= MAX; i++) {     //产生随机数列
    number[i] = rand() % 10;
}
 
quicksort(number, 1, MAX);      //快速排序
 
printf("数列：");                //打印排序后的数列
for(i = 1; i <= MAX; i++)
    printf("%d ", number[i]);
find = 7;                      //要寻找的对象
if((i = fibsearch(number, find)) >= 0)
    printf("找到数字于索引 %d ", i);
else
    printf("\n找不到指定数");
 
printf("\n"); 
}
//建立费氏数列，总共求得MAX+1个斐波那契数
void createfib(void) {
    int i;
    Fib[0] = 0;
    Fib[1] = 1;
    
    for(i = 2; i < MAX; i++)
        Fib[i] = Fib[i-1] + Fib[i-2];
}
 
//找x值
int findx(int n) {
    int i = 0;
    while(Fib[i] <= n)
        i++;
    i--;
    return i;//找到第i个Fib元素小于等于MAX+1
}
 
//费式搜寻
int fibsearch(int number[], int find) {
    int i, x, m;
    
    createfib();                    //创建斐波那契数列
    
    x  = findx(MAX+1);              //斐波那契数列中第x个数刚好不大于MAX+1。MAX是确定的，所以比较的起始点是确定的。
    m = MAX - Fib[x];               //得到一个较小的差值。m的值也是确定的。
    printf("\nx = %d, m = %d, Fib[x] = %d\n\n",
           x, m, Fib[x]);
    
    x--;
    
    i = x;
    
    if(number[i] < find)            //i的初值也是确定的。
        i += m;
    
    while(Fib[x] > 0) {             //搜寻，x值不断减小，范围越来越小，搜寻越来越精细
        if(number[i] < find)        //小于被搜寻的值
            i += Fib[--x];          //右移搜寻位置
        else if(number[i] > find)   //大于被搜寻值
            i -= Fib[--x];          //左移搜寻位置
        else
            return i;               //相等，找到
    }
    return -1;                      //搜寻步子已经最小，还是没找到，搜寻结束
}
 
//快速排序
void quicksort(int number[], int left, int right) {
    int i, j, k, s;
    
    if(left < right) {
        s = number[(left+right)/2];
        i = left - 1;
        j = right + 1;
        
        while(1) {
            while(number[++i] < s) ;        // 向右找
            while(number[--j] > s) ;        // 向左找
            if(i >= j)
                break;
            SWAP(number[i], number[j]);
        }
        
        quicksort(number, left, i-1);       // 对左边进行递回
        quicksort(number, j+1, right);      // 对右边进行递回
    } 
} 
