//一只刚出生的奶牛，4年生1只奶牛，以后每一年生1只。现在给你一只刚出生的奶牛，求20年后有多少奶牛。

//本题主要考察读者的分析能力，已知条件有两：
//第一次，4年生一只。
//然后每年生一只。

//需要的结果中也提供了一个条件，就是20年。读者要注意的本题最难的地方是不光这只奶牛会生奶牛，它的孩子的孩子也会继续生奶牛，读者通过分析下面的代码就能看到难点所在。

#include <stdio.h>

int CalCowsNum(int iYear){
    int iCnt =0;
    long lCowsNum = 1;  //奶牛总数
    for(iCnt=1; iCnt<=iYear; iCnt++){
        if(iCnt>=4){  //4年以后奶牛数量开始增多
            if((iYear-iCnt)>3){  //第2个4年开始后产的奶牛开始生新奶牛
                lCowsNum += CalCowsNum(iYear - iCnt);
            }else{
                lCowsNum++;
            }
        }
    }

    return lCowsNum;    //返回奶牛总数
}

int main(){
    int iYear =0;
    printf("Please input require years:");
    scanf ("%d", &iYear);  //输入年数
    printf("In %d years, There is %d cows.\n", iYear, CalCowsNum(iYear));  //输出结果

    return 0;
}


//运行结果：
//Please input require years:20
//In 20 years, There is 345 cows.
