//下面的代码，提示用户输入一个整数，并判断是否是素数，如果是将输出它本身，否则输出所有的真因子。


#include <stdio.h>

int main(void) {
    int n,
    lcv,
    flag;  // flag 被初始化为 1，如果后续判断 n 不是素数，那么它将变为 0

    printf("Enter value of N > ");
    scanf("%d", &n);
    for (lcv=2, flag=1; lcv <= (n / 2); lcv++) {
        if ((n % lcv) == 0) {
            if (flag)
                printf("The non-trivial factors of %d are: \n", n);
            flag = 0;
            printf("\t%d\n", lcv);
        }
      }
      if (flag)
        printf("%d is prime\n", n);
}


//可能的输出结果：
//Enter value of N > 100 The non-trivial factors of 100 are:
//    2
//    4
//    5
//    10
//    20
//    25
//    50
