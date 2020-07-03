/*
 得分排行
 说明假设有一教师依学生座号输入考试分数，现希望在输入完毕后自动显示学生分数的排行，
 当然学生的分数可能相同。
 解法这个问题基本上要解不难，只要使用额外的一个排行阵列走访分数阵列就可以了，直接
 使用下面的程式片段作说明：
 for(i = 0; i < count; i++) {
   juni[i] = 1;
   for(j = 0; j < count; j++) {
     if(score[j] > score[i])
       juni[i]++;
   }
 }
 printf("得分\t排行\n");
 for(i = 0; i < count; i++)
 printf("%d\t%d\n", score[i], juni[i]);
 上面这个方法虽然简单，但是反覆计算的次数是n^2，如果n值变大，那么运算的时间就会拖长；
 改变juni阵列的长度为n+2，并将初始值设定为0，如下所示：
 接下来走访分数阵列，并在分数所对应的排行阵列索引元素上加1，如下所示：
 将排行阵列最右边的元素设定为1，然后依序将右边的元素值加至左边一个元素，最后排行阵列
 中的「分数+1」」就是得该分数的排行，如下所示：
 这样的方式看起来复杂，其实不过在计算某分数之前排行的人数，假设89分之前的排行人数为x
 人，则89分自然就是x+1了，这也是为什么排行阵列最右边要设定为1的原因；如果89分有y人，
 则88分自然就是x+y+1，整个阵列右边元素向左加的原因正是如此。
 如果分数有负分的情况，由于C/C++或Java等程式语言无法处理负的索引，所以必须加上一个
 偏移值，将所有的分数先往右偏移一个范围即可，最后显示的时候记得减回偏移值就可以了。
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MIN 0
int main(void) {
    int score[MAX+1] = {0};
    int juni[MAX+2] = {0};
    int count = 0, i;
    do {
        printf("输入分数，-1结束：");
        scanf("%d", &score[count++]);
    } while(score[count-1] != -1);
    count--;
    for(i = 0; i < count; i++)
        juni[score[i]]++;
    juni[MAX+1] = 1;
    for(i = MAX; i >= MIN; i--)
        juni[i] = juni[i] + juni[i+1];
    printf("得分\t排行\n");
    for(i = 0; i < count; i++)
        printf("%d\t%d\n", score[i], juni[score[i]+1]);
    return 0;
}
