#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f  //表示∞
#define MAXN 100 //问题表示

using namespace std;

int n; //图顶点个数
int a[MAXN][MAXN]; //图的邻接矩阵
int v; //源点
//求解结果表示
int dist[MAXN]; //dist[i]源点到顶点i的最短路径长度
int prev[MAXN]; //prev[i]表示源点到j的最短路径中顶点j的前驱顶点
int m,t;	//m条边, t为目标点

struct NodeType
{
	int vno;
	int length;
	bool operator<(const NodeType &s) const
	{
		return length>s.length;	//length越小越优先出队
	}
};

void Init()
{
	int x, y, len;
	cout<<"Please enter :"<<endl;
	cout<<"Number of nodes, number of edges, starting point, target point :";
	cin>>n>>m>>v>>t;
	memset(dist,INF,sizeof(dist));
	memset(a,INF,sizeof(a));
	for(int i=0;i<m;i++)	//建图--有向图
	{
		cout<<"Please enter :"<<endl;
		cout<<"Line :";
		cin>>x;
		cout<<"Row :";
		cin>>y;
		cout<<"Len :";
		cin>>len;
		a[x][y]=len;
	}
	for(int i = 0; i < n; i++)	//初始化--头结点指向自己(自己是自己的源结点)
    {
        prev[i]=i;
    }
}

void bfs()
{
	NodeType e, e1;
	priority_queue<NodeType> pqu;
	e.vno = v;//建立源点结点e（根结点）
	e.length = 0;
	pqu.push(e);//源点结点e进队
	dist[v] = 0;
	while(!pqu.empty())//队列不空循环
	{
		e = pqu.top();
		pqu.pop();
		for(int j=0;j<n;j++)
		{
			if(a[e.vno][j] < INF && e.length+a[e.vno][j] < dist[j])
			{	//剪枝：e.vno到顶点j有边并且路径长度更短
				dist[j] = e.length + a[e.vno][j];
				prev[j] = e.vno;
				e1.vno = j;	//建立相邻点j的结点e1
				e1.length = dist[j];
				pqu.push(e1);//结点e1进队
			}
		}
	}
}

void OutPutPath(int i)
{
    if(i == prev[i])
    {
        cout << i;
    }
    else
    {
        OutPutPath(prev[i]);
        cout << " " << i;
    }
//    cout << endl;
}

void OutPut()
{
    cout << "点" << v << "到"<< t << "的最短距离是" << dist[t] << endl;
    cout << "路径为：";
    OutPutPath(t);
}

int main()
{
	Init();
	bfs();
	OutPut();
	return 0;
}

