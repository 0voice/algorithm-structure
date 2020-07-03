/*
 长PI
 说明圆周率后的小数位数是无止境的，如何使用电脑来计算这无止境的小数是一些数学家与
 程式设计师所感兴趣的，在这边介绍一个公式配合大数运算，可以计算指定位数的圆周率。
 解法首先介绍J.Marchin的圆周率公式：
 PI = [16/5 - 16 / (3*53) + 16 / (5*55) - 16 / (7*57) + ......] -
 [4/239 - 4/(3*2393) + 4/(5*2395) - 4/(7*2397) + ......]
 可以将这个公式整理为：
 PI = [16/5 - 4/239] - [16/(53) - 4/(2393)]/3+ [16/(55) - 4/(2395)]/5 + ......
 也就是说第n项，若为奇数则为正数，为偶数则为负数，而项数表示方式为：
 [16/52*n-1 - 4/2392*n-1] / (2*n-1)
 如果我们要计算圆周率至10的负L次方，由于[16/52*n-1 - 4/2392*n-1]中16/52*n-1比4/2392*n-1来的
 大，具有决定性，所以表示至少必须计算至第n项：
 [16/52*n-1 ] / (2*n-1) = 10-L
 将上面的等式取log并经过化简，我们可以求得：
 n = L / (2log5) = L / 1.39794
 所以若要求精确度至小数后L位数，则只要求至公式的第n项，其中n等于：
 n = [L/1.39794] + 1
 在上式中[]为高斯符号，也就是取至整数（不大于L/1.39794的整数）；为了计简方便，可以在程
 式中使用下面这个公式来计简第n项：
 [Wn-1/52- Vn-1 / (2392)] / (2*n-1)
 这个公式的演算法配合大数运算函式的演算法为： div(w, 25, w);
 div(v, 239, v);
 div(v, 239, v);
 sub(w, v, q);
 div(q, 2*k-1, q)
 至于大数运算的演算法，请参考之前的文章，必须注意的是在输出时，由于是输出阵列中的整
 数值，如果阵列中整数位数不满四位，则必须补上0，在C语言中只要使用格式指定字%04d，
 使得不足位数部份自动补上0再输出，至于Java的部份，使用NumberFormat来作格式化。
*/

#include <stdio.h>
#define L 1000
#define N L/4+1
// L 为位数，N是array长度
void add(int*, int*, int*);
void sub(int*, int*, int*);
void div(int*, int, int*);
int main(void) {
    int s[N+3] = {0};
    int w[N+3] = {0};
    int v[N+3] = {0};
    int q[N+3] = {0};
    int n = (int)(L/1.39793 + 1);
    int k;
    w[0] = 16*5;
    v[0] = 4*239;
    for(k = 1; k <= n; k++) {
        // 套用公式
        div(w, 25, w);
        div(v, 239, v);
        div(v, 239, v);
        sub(w, v, q);
        div(q, 2*k-1, q);
        if(k%2) // 奇数项
            add(s, q, s);
        else // 偶数项
            sub(s, q, s);
    }
    printf("%d.", s[0]);
    for(k = 1; k < N; k++)
        printf("%04d", s[k]);
    printf("\n");
    return 0;
}
void add(int *a, int *b, int *c) {
    int i, carry = 0;
    for(i = N+1; i >= 0; i--) {
        c[i] = a[i] + b[i] + carry;
        if(c[i] < 10000)
            carry = 0;
        else { // 进位
            c[i] = c[i] - 10000;
            carry = 1;
        }
    }
}
void sub(int *a, int *b, int *c) {
    int i, borrow = 0;
    for(i = N+1; i >= 0; i--) {
        c[i] = a[i] - b[i] - borrow;
        if(c[i] >= 0)
            borrow = 0;
        else { // 借位
            c[i] = c[i] + 10000;
            borrow = 1;
        }
    }
}
void div(int *a, int b, int *c) { // b 为除数
    int i, tmp, remain = 0;
    for(i = 0; i <= N+1; i++) {
        tmp = a[i] + remain;
        c[i] = tmp / b;
        remain = (tmp % b) * 10000;
    }
}
