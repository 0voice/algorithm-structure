/*
3只LED数码管各自按不同的速度快速滚动0~9的随机数10s后停止，
由1只按键启动。10s内出现三数相同时，停止显示，蜂鸣器鸣响，
1只LED灯闪亮。
*/

#include <reg52.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint  unsigned int

// 按键
sbit Button = P3 ^ 5;

// 蜂鸣器
sbit Beep   = P3 ^ 6;

// LED
sbit LED    = P1 ^ 7;

// 数码管位选
sbit P2_0 = P2 ^ 0;
sbit P2_1 = P2 ^ 1;
sbit P2_2 = P2 ^ 2;
sbit P2_3 = P2 ^ 3;

uchar num_1=0, num_2=0, num_3=0, num_4=0;

uchar clock=0;

uchar code table[] =
{
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
//  0     1     2     3     4     5     6     7     8     9
};// 共阴极
//uchar code table[]={
//    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90
////  0     1     2     3     4     5     6     7     8     9
//};// 共阳极

// 延时函数
void delay_ms(uint xms)
{
	uint i, j;
	for (i = 0; i<xms; i++)
        for (j = 0; j<110; j++);
}

void display(uchar num1, uchar num2, uchar num3, uchar num4)
{
    P0=table[num1];
    P2_0 = 0;
    delay_ms(5);
    P2_0 = 1;

    P0=table[num2];
    P2_1 = 0;
    delay_ms(5);
    P2_1 = 1;

    P0=table[num3];
    P2_2 = 0;
    delay_ms(5);
    P2_2 = 1;
    
    P0=table[num4];
    P2_3 = 0;
    delay_ms(5);
    P2_3 = 1;
}

uchar keyScan()
{
    if(Button==0)
    {
        delay_ms(5);	    // 消抖动
        if(Button==0)	    // 确认按键被按下
        {
            while(!Button); // 松手检测
            return 1;
        }
    }
    return 0;
}

void InitTimer0()
{
    TMOD &= 0xf0;
    TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;   // 50ms
	EA = 1;
	ET0 = 1;
}

void T0_time() interrupt 1
{
    static uchar num;
	TH0 = (8192-4607)/32;
	TL0 = (8192-4607)%32;
	num++;
    
    // 0.5s
    if (num % 100 == 0)
    {
        num_1 = rand()%9;
    }
    // 0.4s
    if (num % 80 == 0)
    {
        num_2 = rand()%9;
    }
    // 0.2s
    if (num % 40 == 0)
    {
        num_3 = rand()%9;
    }
    // 0.1s
    if (num % 20 == 0)
    {
        num_4 = rand()%9;
    }
    if (num == 200)
    {
        clock ++;
        num = 0;
    }
}

void InitTimer1()		//256微秒@11.0592MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0x14;		//设置定时初值
	TH1 = 0x14;		//设置定时重载值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
    ET1 = 0;
}

void main()
{
    LED = 1;
    InitTimer0();
    InitTimer1();
    while(1)
    {
        if (keyScan() && clock == 0)
        {
            TR0 = 1;    // 开启定时器
            srand(TL1);
            LED = 1;
        }
        if (clock == 10)
        {
            TR0 = 0;    // 关闭定时器
            clock = 0;
        }
        
        display(num_1, num_2, num_3, num_4);
        
        if ((num_1 == num_2) && (num_2 == num_3) && (num_3 == num_4) && (clock != 0))
        {
            TR0 = 0;    // 关闭定时器
            clock = 0;
            
            // 打开蜂鸣器
            Beep = 0;
            delay_ms(500);
            Beep = 1;
            
            // 打开LED
            LED = 0;
        }
    }
}
