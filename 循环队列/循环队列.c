#include <stdio.h>

#define M_S 20			//定义数组长度，限制元素个数
//定义结构体
struct Queue
{
        int a[M_S];
        int front;		//前指针，指向队首
        int rear;		//后指针，指向对尾
};
//初始化
void InitQueue(struct Queue *p)
{
        p->front=p->rear=0;			//初始化前后指针都指向0
}
//求长度
int QueueLength(struct Queue *p)
{
        return (p->rear-p->front+M_S)%M_S;	//求元素个数
}
//判断是否为空
short IsEmpty(struct Queue *p)
{
        if(p->front==p->rear)		//若前后指针指向同一个节点，则判断为空
                return 1;
        else
                return 0;
}
//判断是否为满
short IsFull(struct Queue *p)
{
        if(p->front==(p->rear+1)%M_S)		//若前指针等于(后指针+1)%数组大小，则判断为满
                return 1;
        else
                return 0;
}
//进队
short EnQueue(struct Queue *p,int key)
{
        if(IsFull(p))				//若队列为满，则进队失败
                return 0;
        p->a[p->rear]=key;			//否则将进队元素赋值给后指针所指的位置，后指针往后移动一格
        p->rear=(p->rear+1)%M_S;
        return 1;
}
//出队
short DeQueue(struct Queue *p,int *value)
{
        if(IsEmpty(p))				//若队列为空，则出队失败
                return 0;
        *value=p->a[p->front];			//传入一个指针保留出队元素，然后队首指向下一个元素
        p->front=(p->front+1)%M_S;
        return 1;
}
int main()
{
        struct Queue c;         //定义结构体
        InitQueue(&c);          //调用初始化函数，初始队列
        EnQueue(&c,1);       	//进队
        EnQueue(&c,2);
        EnQueue(&c,3);
        EnQueue(&c,4);
        int value;              //出队，输出
        while(DeQueue(&c,&value))
        {
                printf("---%d出队---还有%d人在队列---\n",value,QueueLength(&c));
                sleep(1);
        }
        return 0;
}

