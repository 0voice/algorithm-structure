//线性同余法产生随机数序列的公式为：
//    x[k+1] = (a*x[k] + c) % m

//参数 a, c, m 都是由用户来设定的，并和一个种子数（例如 x[0]）一起作为命令行参数传递给生成的程序。

//一个简单的例子：a=7, c=1, m=13, and seed=5

//一个复杂的例子：a=69069, c=0, m=2^32=4294967296, seed=31

//下面的代码将输出一个随机数序列（最多有 m-1 个不同的值），然后继续循环。


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <Windows.h>

static long seed = 13;
static long a;
static long c;
static long m;

void random_init(long s) {
    if (s != 0) seed = s;
}

long random() {
    seed = (a*seed + c)%m;
    return seed;
}

int main(int argc, char * argv[]) {
    long s;
    int k;
    if (argc != 5) {
        printf("usage: %s a, c, m, seed\n", argv[0]);
        return 1;
    }
    a = atoi(argv[1]);
    c = atoi(argv[2]);
    m = atoi(argv[3]);
    s = atoi(argv[4]);
    random_init(s);
  
    for (k = 0; k < m-1; k++) {
        printf("%8ld", random());
        if (k % 8 == 7) {  // 输出 8 个数字以后换行
            printf("\n");
            Sleep(1);  // 暂停 1 秒
        }
    }
    printf("\n");
    return 0;
}
