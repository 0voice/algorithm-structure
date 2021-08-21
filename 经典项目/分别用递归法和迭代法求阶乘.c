#include <stdio.h>
#include <time.h>

// 递归计算阶乘
long factorial_recursion(int n){
    if(n<=0){
        return 1;
    }else{
        return n * factorial_recursion(n-1);
    }
}

// 迭代计算阶乘
long factorial_iteration(int n){
    int result = 1;

    while(n>1){
        result *= n;
        n--;
    }

    return result;
}


int main(){
    int N  = 10;
    long recursion_result = factorial_recursion(N);
    long iteration_result = factorial_iteration(N);

    // %ld 输出长整型，即 long int
    printf("The factorial(recursion) of %ld is %ld!\n", N, recursion_result);
    printf("The factorial(iteration) of %ld is %ld!\n", N, iteration_result);

    return 0;
}


//运行结果：

//The factorial(recursion) of 10 is 3628800!
//The factorial(iteration) of 10 is 3628800!
