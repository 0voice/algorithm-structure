/**
 * C: 邻接矩阵表示的"有向图(Matrix Directed Graph)"
 *
 * @author skywang
 * @date 2014/04/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

// 邻接矩阵
typedef struct _graph
{
    char vexs[MAX];       // 顶点集合
    int vexnum;           // 顶点数
    int edgnum;           // 边数
    int matrix[MAX][MAX]; // 邻接矩阵
}Graph, *PGraph;

/*
 * 返回ch在matrix矩阵中的位置
 */
static int get_position(Graph g, char ch)
{
    int i;
    for(i=0; i<g.vexnum; i++)
        if(g.vexs[i]==ch)
            return i;
    return -1;
}

/*
 * 读取一个输入字符
 */
static char read_char()
{
    char ch;

    do {
        ch = getchar();
    } while(!isLetter(ch));

    return ch;
}

/*
 * 创建图(自己输入)
 */
Graph* create_graph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    Graph* pG;
    
    // 输入"顶点数"和"边数"
    printf("input vertex number: ");
    scanf("%d", &v);
    printf("input edge number: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1))))
    {
        printf("input error: invalid parameters!\n");
        return NULL;
    }
    
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgnum = e;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i] = read_char();
    }

    // 初始化"边"
    for (i = 0; i < pG->edgnum; i++)
    {
        // 读取边的起始顶点和结束顶点
        printf("edge(%d):", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1==-1 || p2==-1)
        {
            printf("input error: invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
    }

    return pG;
}

/*
 * 创建图(用已提供的矩阵)
 */
Graph* create_example_graph()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'B'}, 
        {'B', 'C'}, 
        {'B', 'E'}, 
        {'B', 'F'}, 
        {'C', 'E'}, 
        {'D', 'C'}, 
        {'E', 'B'}, 
        {'E', 'D'}, 
        {'F', 'G'}}; 
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    Graph* pG;
    
    // 输入"顶点数"和"边数"
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++)
    {
        pG->vexs[i] = vexs[i];
    }

    // 初始化"边"
    for (i = 0; i < pG->edgnum; i++)
    {
        // 读取边的起始顶点和结束顶点
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        pG->matrix[p1][p2] = 1;
    }

    return pG;
}

/*
 * 打印矩阵队列图
 */
void print_graph(Graph G)
{
    int i,j;

    printf("Martix Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            printf("%d ", G.matrix[i][j]);
        printf("\n");
    }
}

void main()
{
    Graph* pG;

    // 自定义"图"(输入矩阵队列)
    //pG = create_graph();
    // 采用已有的"图"
    pG = create_example_graph();

    print_graph(*pG);       // 打印图
}
