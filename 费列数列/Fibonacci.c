/*

费式数列

*/
#include <stdio.h>
#include <stdlib.h>
#define N 20
int main(void) {
    int Fib[N] = {0};
    int i;
    Fib[0] = 0;
    Fib[1] = 1;
    for(i = 2; i < N; i++)
        Fib[i] = Fib[i-1] + Fib[i-2];
    for(i = 0; i < N; i++)
        printf("%d ", Fib[i]);
    printf("\n");
    return 0;
}
