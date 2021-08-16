#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

#define MAX 10000 //MAX表示最大节点数
#define INF 10000 //设定两个节点之间不可达的情况下权重为INF

struct edge {
    int to,cost;      //每条边都有一个目的节点和权重
};


vector<edge> es[MAX]; //边的数组元素是以edge为元素的队列

int d[MAX];  //节点i到所有节点的距离
int v,e;  //节点个数和边的个数

//构造图
void build()
{
    printf("please input the number of vertex and edge\n");
    scanf("%d %d",&v,&e);
    printf("please input from,to,and cost of all edges\n");
    for(int i=0;i<e;i++)
    {
        int from,to,cost;
        edge epair1,epair2;
        scanf("%d %d %d",&from,&to,&cost);
        epair1.to=to;
        epair1.cost=cost;
        es[from].push_back(epair1);
        epair2.to=from;
        epair2.cost=cost;
        es[to].push_back(epair2);
    }
}
//求得节点s到所有节点的最短路径
void shortest_path(int s)
{
    for(int i=0;i<v;i++)
    {
        d[i]=INF;
    }
    d[s]=0;
    while(true)
    {
        bool update = false;
            for(int i=0;i<v;i++)
    {
        for(int j=0;j<es[i].size();j++)
        {
            if(d[i]!=INF&&es[i][j].cost+d[i]<d[es[i][j].to])
            {
                d[es[i][j].to]=d[i]+es[i][j].cost;
                update = true;
            }
        }
    }
    if(!update)
    {
        break;
    }
    }

}

int main()
{
    build();
    shortest_path(0);
    for(int i=0;i<v;i++)
    {
        printf("%d ",d[i]);
    }
    return 0;
}
