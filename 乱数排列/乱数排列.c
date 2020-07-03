/*
 洗扑克牌（乱数排列）
 说明
 洗扑克牌的原理其实与乱数排列是相同的，都是将一组数字（例如1～N）打乱重新排列，只
 不过洗扑克牌多了一个花色判断的动作而已。
 解法
 初学者通常会直接想到，随机产生1～N的乱数并将之存入阵列中，后来产生的乱数存入阵列
 前必须先检查阵列中是否已有重复的数字，如果有这个数就不存入，再重新产生下一个数，运
 气不好的话，重复的次数就会很多，程式的执行速度就很慢了，这不是一个好方法。
 以1～52的乱数排列为例好了，可以将阵列先依序由1到52填入，然后使用一个回圈走访阵列，
 并随机产生1～52的乱数，将产生的乱数当作索引取出阵列值，并与目前阵列走访到的值相交换，
 如此就不用担心乱数重复的问题了，阵列走访完毕后，所有的数字也就重新排列了。
 至于如何判断花色？这只是除法的问题而已，取商数判断花色，取余数判断数字，您可以直接
 看程式比较清楚。
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 52
int main(void) {
    int poker[N + 1];
    int i, j, tmp, remain;
    // 初始化阵列
    for(i = 1; i <= N; i++)
        poker[i] = i;
    srand(time(0));
    // 洗牌
    for(i = 1; i <= N; i++) {
        j = rand() % 52 + 1;
        tmp = poker[i];
        poker[i] = poker[j];
        poker[j] = tmp;
    }
    for(i = 1; i <= N; i++) {
        // 判断花色
        switch((poker[i]-1) / 13) {
            case 0:
                printf("桃"); break;
            case 1:
                printf("心"); break;
            case 2:
                printf("砖"); break;
            case 3:
                printf("梅"); break;
        }
        // 扑克牌数字
        remain = poker[i] % 13;
        switch(remain) {
            case 0:
                printf("K "); break;
            case 12:
                printf("Q "); break;
            case 11:
                printf("J "); break;
            default:
                printf("%d ", remain); break;
        }
        if(i % 13 == 0)
            printf("\n");
    }
    return 0;
}
