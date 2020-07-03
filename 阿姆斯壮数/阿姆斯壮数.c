/*
 阿姆斯壮数
*/

#include <stdio.h>
#include <time.h>
#include <math.h>
int main(void) {
    int a, b, c;
    int input;
    printf("寻找Armstrong数：\n");
    for(input = 100; input <= 999; input++) {
        a = input / 100;
        b = (input % 100) / 10;
        c = input % 10;
        if(a*a*a + b*b*b + c*c*c == input)
            printf("%d ", input);
    }
    printf("\n");
    return 0;
}
