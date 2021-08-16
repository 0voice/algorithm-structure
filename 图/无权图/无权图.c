#include <stdio.h>
#include <stdlib.h>

/*
 * Algorithm thought:
 * We easily know this question is BFS.
 * we  access the first level nodes, then access second level nodes
 * until we reach the sixth level.
 * We let every node to BFS until it reach the sixth level,then we record the total nodes M
 * it can reach, calculate the M/N(The total point the test data gives) .
 */

#define MAX_VERTEX_MUM 10001
typedef int vertex; /*vertex is the index of point in the graph*/
typedef int dataType; /*dataType is the data type of vertex */
typedef int weightType; /*The data type of weight  */

/*
 * Define a data structure to edge
*/
typedef struct eNode *ptrToENode;
typedef struct eNode {
     vertex v1, v2;
     weightType wight;
};

typedef ptrToENode edge;
 
/*
 * Define a data structure for adjacent table node
*/
typedef struct adjNode *ptrToAdjNode;
typedef struct adjNode {
    vertex adjVertex; /*The index of vertex in the graph*/
    weightType weight; /*the value of the weight*/
    ptrToAdjNode next; /*A point to point next node*/
};
 
/*
 * Define a data structure for adjacent table head point
*/
typedef struct vNode *ptrToVNode;
typedef struct vNode {
   dataType data; /*The value of every vertex,some times it will be ignore*/
   ptrToAdjNode head;/*The point to point the adjacent table first element*/
} adjList[MAX_VERTEX_MUM];

/*Define a data structure for graph*/
typedef struct gNode *ptrToGNode;
typedef struct gNode {
    int vertex_num;
    int edge_num;
    adjList g;
};

typedef ptrToGNode adjacentTableGraph; /*a graph show by adjacent table*/
 
/*
  create a graph given the vertex number.
  @param vertexNum The verter number of the graph
  @return a graph with vertex but no any egdgs
*/
ptrToGNode createGraph(int vertexNum) {
   vertex v;
   adjacentTableGraph graph = (adjacentTableGraph) malloc(
           sizeof(struct gNode));
   graph->vertex_num = vertexNum;
   graph->edge_num = 0;
   for (v = 1; v <= graph->vertex_num; v++) {
        graph->g[v].head = NULL;
   }
   return graph;
}

/*
 insert a edge to graph.We will distinct oriented graph and undirected graph
 The e->v1 and e->v2 are the vertexs' indexs in the adjacent table
 @param graph The graph you want to insert edge
 @param e The edge you want to insert the graph
 @param isOriented Whether the graph is oriented graph.If the graph is oriented
 we will set adjacent table graph[v1]->head=v2 and set graph[v1].head=v2
 otherwise we only set graph[v1].head=v2
*/
void insertEdge(adjacentTableGraph graph, edge e, int isOriented) {
    ptrToAdjNode newNode;
     newNode = (ptrToAdjNode) malloc(sizeof(struct adjNode));
     newNode->adjVertex = e->v2;
     newNode->weight = e->wight;
     newNode->next = graph->g[e->v1].head;
     graph->g[e->v1].head = newNode;
     if (!isOriented) {
         newNode = (ptrToAdjNode) malloc(sizeof(struct adjNode));
         newNode->adjVertex = e->v1;
         newNode->weight = e->wight;
         newNode->next = graph->g[e->v2].head;
         graph->g[e->v2].head = newNode;
    }
 }
 
 adjacentTableGraph buildGraph(int isordered) {
     adjacentTableGraph graph;
     edge e;
     vertex v;
     int vertex_num;
     scanf("%d", &vertex_num);
     graph = createGraph(vertex_num);
     scanf("%d", &(graph->edge_num));
     if (graph->edge_num) {
         e = (edge) malloc(sizeof(struct eNode));
        for (v = 0; v < graph->edge_num; v++) {
             scanf("%d %d", &e->v1, &e->v2);
            e->v1--;
             e->v2--;
             e->wight = 1;
             insertEdge(graph, e, isordered);
         }
     }
     return graph;
 }
 
 /*==============================define a queue=====================================================*/
 /*define a list to store the element in the queue*/
 typedef vertex elementType;
 typedef struct node *pList;
 typedef struct node {
     elementType element;
     struct node *next;
 };
 
 /*define a queue to point the list*/
 typedef struct node2 *pQueue;
 typedef struct node2 {
     pList front; /*the front point to point the head of the list*/
     pList rear; /*the rear point to point the rear of of the list*/
 };
 
 /*create a empty list to store the queue element*/
 pList createEmptyList() {
     pList list;
     list = (pList) malloc(sizeof(struct node));
     list->next = NULL;
     return list;
 }

 /*create a empty queye*/
 pQueue createEmptyQueue() {
     pQueue queue = (pQueue) malloc(sizeof(struct node2));
     queue->front = NULL;
     queue->rear = NULL;
     return queue;
 }
 
 /*
  Wether the queue is empty
  @param queue The queue need to adjust
  @return If the queue is null,return 1 otherwise return 0
  */
 int isQueueEmpty(pQueue queue) {
     return (queue->front == NULL);
 }
 
 /*
  Add a element to a queue,If the queue is null,we will create a new queue
  @parama queue The queue we will add elememt to
  @prama element The element we will add to queue
  */
 void addQueue(pQueue queue, elementType element) {
     if (isQueueEmpty(queue)) {
         pList list = createEmptyList();
         list->element = element;
         queue->front = queue->rear = list;
     } else {
       pList newNode = (pList) malloc(sizeof(struct node));
        newNode->element = element;
        newNode->next = queue->rear->next;
         queue->rear->next = newNode;
        queue->rear = newNode;
    }
 }
 
 /*
  delete a element from a queue
  @param queue The queue will be deleted a element
  @return The element has been deleted
  */
 elementType deleteEleFromQueue(pQueue queue) {
     if (isQueueEmpty(queue)) {
         printf("the queue is empty,don't allow to delete elemet from it!");
         return -1;
     } else {
        pList oldNode = queue->front;
         elementType element = oldNode->element;
         if (queue->front == queue->rear) {
             queue->rear = queue->front = NULL;
         } else {
             queue->front = queue->front->next;
         }
         free(oldNode);
         return element;
     }
 }
 
 
 void unWeight(adjacentTableGraph graph, int *dist, int *path, vertex startPoint) {
    dist[startPoint] = 0;
     vertex v;
     ptrToAdjNode w;
     pQueue queue = createEmptyQueue();
     addQueue(queue, startPoint);
     while (!isQueueEmpty(queue)) {
         v = deleteEleFromQueue(queue);
         for (w = graph->g[v].head; w; w = w->next) {
             if (dist[w->adjVertex] == -1) {
                 addQueue(queue, w->adjVertex);
                 dist[w->adjVertex] = dist[v] + 1;
                 path[w->adjVertex] = v;
             }
         }
     }
 }
 
 /*
  * Fill a array with value
  * @param arr The array need to be filled
  * @param length The length of the array
  * @param filledValue The value the array will be filled
*/
void fullArray(int *arr, int length, int filledValue) {
    int i;
    for (i = 0; i < length; i++) {
        arr[i] = filledValue;
    }
}
 
/*============================define a stack to print result=============*/
typedef int stackElement;
typedef struct node3 {
    stackElement element;
    struct node3 *next;
} sta, *pStack;
 
pStack createEmptyStack() {
    pStack stack;
    stack = (pStack) malloc(sizeof(sta));
    if (stack) {
        stack->next = NULL;
    }
    return stack;
}
 
int isEmpty(pStack stack) {
    if (stack->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}
 
void push(pStack stack, stackElement element) {
    pStack node = (pStack) malloc(sizeof(sta));
    node->element = element;
    node->next = stack->next;
    stack->next = node;
}

stackElement pop(pStack stack) {
    stackElement element;
    pStack topHead;
    if (isEmpty(stack)) {
        printf("the stack is empty,can not pop");
        return -65536;
    } else {
        topHead = stack->next;
        stack->next = topHead->next;
        element = topHead->element;
        free(topHead);
        return element;
    }
}

void findPath(int *path, int length, int destination) {
    pStack stack = createEmptyStack();
    vertex v;
    int index = destination;
    push(stack, index);
    while (v != -1) {
        v = path[index];
        push(stack, v);
        index = v;
    }

    pop(stack);
    while (!isEmpty(stack)) {
        stackElement element = pop(stack);
        printf("%d ", element+1);
    }
}
 
int main() {
    adjacentTableGraph graph = buildGraph(1);
    int dist[graph->vertex_num];
    int path[graph->vertex_num];
    fullArray(dist, graph->vertex_num, -1);
    fullArray(path, graph->vertex_num, -1);
    unWeight(graph, dist, path, 2);
    findPath(path, graph->vertex_num, 6);
    printf("just test");
    return 0;
}
