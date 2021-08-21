//这个其实不难，就是用到一个简单的Windows API，代码请见解析。

//获取开机时间要用到 GetTickCount() 这个 API，功能是获取重系统开始到运行时的时间。代码如下：


#include<stdio.h>
#include<windows.h>

int main()
{
    DWORD k = GetTickCount();
    int s = k/1000;
    int min = 0, h = 0;
    if (s >= 60){
        min = s / 60;
        s = s % 60;
    }
    if (min >= 60){
        h = min / 60;
        min = min % 60;
    }
    printf("重系统启动到现在过了的时间：%d h %d min %d s\n",h,min,s);

    system("pause");
    return 0;
}

//运行结果：
//重系统启动到现在过了的时间：40 h 20 min 33 s
//请按任意键继续. . .
