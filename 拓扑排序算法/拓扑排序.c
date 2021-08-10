#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef int VertexType;
Boolean visit[MaxVertexNum];
typedef struct node
{
    int adjvex;
    struct node *next;
}EdgeNode;

typedef struct
{
    VertexType vertex;
    EdgeNode *firstedge;
}VertexNode;

typedef VertexNode AdjList[MaxVertexNum];

typedef struct
{
    AdjList adjlist;
    int n,e;
}ALGraph;

int FindVertex(ALGraph *G ,int e,int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        if(G->adjlist[i].vertex==e)
        {
            return i;
        }
    }
    return -1;
}
void create(ALGraph *G)			//创建邻接表
{
    int i,j,k,w,v;
    EdgeNode *s;

    printf("读入顶点和边数");
    scanf("%d %d",&G->n,&G->e);

    for(i=0;i<G->n;i++)
    {

        printf("建立顶点表");
        fflush(stdin);
        scanf("%d",&G->adjlist[i].vertex);
        G->adjlist[i].firstedge=NULL;
    }
    printf("建立边表\n");
    for(k=0;k<G->e;k++)
    {
        printf("读入(vi-vj)的顶点对序号");
        scanf("%d %d",&i,&j);

        i=FindVertex(G,i,G->n);
        j=FindVertex(G,j,G->n);
        if(i==-1||j==-1)
        {
            printf("找不到顶点，请重新输入!\n");
            printf("读入(vi-vj)的顶点对序号");
            scanf("%d %d",&i,&j);
            i=FindVertex(G,i,G->n);
            j=FindVertex(G,j,G->n);
        }
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=(j);
        s->next=G->adjlist[i].firstedge;
        G->adjlist[i].firstedge=s;
    }
}

void TopoSort(ALGraph *G,int n)
{
    int i,j,k,top,m=0;
    EdgeNode *p;
    int *d=(int *)malloc(n*sizeof(int));		
    for(i=0;i<n;i++)		//初始化数组
    {
        d[i]=0;
    }
    for(i=0;i<n;i++)		//统计各个顶点的入度情况，并把他们填入数组里面
    {
        p=G->adjlist[i].firstedge;
        while(p!=NULL)
        {
            j=p->adjvex;
            d[j]++;
            p=p->next;
        }
    }
    top=-1;
    for(i=0;i<n;i++)			//先找出里面入度是0的顶点
    {
        if(d[i]==0)
        {
            d[i]=top;
            top=i;
        }
    }

    while(top!=-1)
    {
        j=top;	
        top=d[top];
        printf("%d ",j);		
        m++;		//统计顶点
        p=G->adjlist[j].firstedge;
        while(p)
        {
            k=p->adjvex;		//相l连接的顶点
            d[k]--;		//相连接的顶点入度减1
            if(d[k]==0)		//如果发现入度为0的新顶点，从该顶点出发
            {
                d[k]=top;
                top=k;
            }
            p=p->next;
        }

    }
    if(m<n) printf("\n有回路！\n");
    free(d);
}

void main()
{
    ALGraph *G=(ALGraph *)malloc(sizeof(ALGraph));
    EdgeNode *p;
    create(G);
    int i;
    printf("其邻接表为('->'表示两个之间有连接)：\n");
    for(i=0;i<G->n;i++)
    {
        p=G->adjlist[i].firstedge;
        printf("%d->",G->adjlist[i].vertex);
        while(p!=NULL)
        {
            printf("%d->",G->adjlist[p->adjvex].vertex);
            p=p->next;
        }
        printf("\n");
    }
    printf("拓扑排序为：\n");
    TopoSort(G,G->n);
}
