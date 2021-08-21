//从键盘输入年号和月号，求这一年的这一月共有多少天。
//分析
//这个问题需要考虑闰年问题，因为二月份的天数与闰年有关。闰年的判断依据是：若某年能被4整除，但不能被100整除，则这一年是闰年；若某年能被400整除，则这一年也是闰年。请考虑：闰年如何表达？

//本题13个分支（比1年12个月共需12个分支多1），编程可使用的多分支结构有哪些？else…if、if…else的嵌套和switch使用哪一个最为简捷？是switch吗？


#include <stdio.h>
#include <stdlib.h>

void main(){ 
    int year, month, days;
    
    printf("输入年份：");
    scanf("%d",&year);
    printf("输入月份："); 
    scanf("%d", &month);

    switch(month){
        case 1: 
        case 3: 
        case 5: 
        case 7: 
        case 8: 
        case 10: 
        case 12:
            days=31;
            break; 
        case 4: 
        case 6: 
        case 9: 
        case 11:
            days=30;
            break; 
        case 2:
            // 判断闰年
            if(year%4==0 && year%100!=0 || year%400==0)
                days=29; 
            else
                days=28; 
            break; 
        default:
            printf("月份输入错误！\n");
            exit(1);
            break; 
    } 
    printf("天数：%d\n", days); 
}


//第一次运行结果：
//输入年份：2014
//输入月份：10
//天数：31

//第二次运行结果：
//输入年份：2013
//输入月份：02
//天数：28

//第三次运行结果：
//输入年份：2000
//输入月份：2
//天数：29
