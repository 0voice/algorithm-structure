/*
 后序式的运算
 说明将中序式转换为后序式的好处是，不用处理运算子先后顺序问题，只要依序由运算式由
 前往后读取即可。
*/

#include <stdio.h>
#include <stdlib.h>
void evalPf(char*);
double cal(double, char, double);
int main(void) {
    char input[80];
    printf("输入后序式：");
    scanf("%s", input);
    evalPf(input);
    return 0;
}
void evalPf(char* postfix) {
    double stack[80] = {0.0};
    char temp[2];
    char token;
    int top = 0, i = 0;
    temp[1] = '\0';
    while(1) {
        token = postfix[i];
        switch(token) {
            case '\0':
                printf("ans = %f\n", stack[top]);
                return;
            case '+': case '-': case '*': case '/':
                stack[top-1] =
                cal(stack[top], token, stack[top-1]);
                top--;
                break;
            default:
                if(top < sizeof(stack) / sizeof(float)) {
                    temp[0] = postfix[i];
                    top++;
                    stack[top] = atof(temp);
                }
                break;
        }
        i++;
    }
}
double cal(double p1, char op, double p2) {
    switch(op) {
        case '+':
            return p1 + p2;
        case '-':
            return p1 - p2;
        case '*':
            return p1 * p2;
        case '/':
            return p1 / p2;
    }
}
