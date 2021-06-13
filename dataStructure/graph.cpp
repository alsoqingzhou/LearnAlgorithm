#include <stdio.h>
const int maxsize = 10010;

// 图的顺序存储结构体定义——利用邻接矩阵
typedef struct {
    int no; //结点编号
    char info; //结点信息
}VertexType; //结点结构体定义
typedef struct {
    int n, e; //分别保存图的结点数和边数
    int edges[maxsize][maxsize]; //整型数组，其中元素为int, 无权图保存边的信息，即横纵坐标之间是否有边
    VertexType vex[maxsize]; //图结点型，保存图的结点信息
}MGraph; //图的邻接矩阵类型


// 图的链式存储结构体定义——利用邻接表
typedef struct ArcNode {
    int adjVex; //构成边的结点的位置
    ArcNode *nextArc; //指向构成下一条边的结点
    int info; //边的信息，如权重
}ArcNode; //边表结点定义
typedef struct {
    char data; //顶点信息
    ArcNode *firstArc; //指向第一条边
}VNode; //顶点表结点定义
typedef struct {
    VNode adjlist[maxsize]; //邻接表数组，为顶点表结点数组，保存顶点表结点
    int n, e; //保存结点数与边数
}AGraph; //图的邻接表类型定义

//基于邻接表的图的深度优先遍历
int visit[maxsize]; //该数组用于标记图中的某个结点是否已经访问过

void Visit(int v) {
    printf("%d", v);
}

void DFS(AGraph *G, int v) {//第一个参数是某个图的指针，第二个参数是图中的开始结点
    ArcNode *p; //指向结点各条边的指针
    visit[v] = 1; //当前结点没有访问过，访问数组标记
    Visit(v); //访问结点
    p = G->adjlist[v].firstArc; //p指向顶点结点的第一条边
    while(p != NULL) {
        if(visit[p->adjVex] == 0) { //当前p边对应的结点没有被访问
            DFS(G, p->adjVex); //从该结点开始递归
        }
        p = p->nextArc; //当前边对应的结点的相邻结点都已经访问结束，p指向下一条边
    }
}

// 基于邻接表的图的广度优先遍历
void BFS(AGraph *G, int v, int visit[maxsize]) {
    ArcNode *p; //指向边的指针
    int que[maxsize], front = rear = 0; //定义队列，依次入队某个结点未访问的邻接点
    int j; //保存出队的结点在顶点数组中的下表

    Visit(v); //访问开始的第一个结点
    visit[v] = 1; //标记已访问

    rear = (rear + 1) % maxsize;
    que[rear] = v; //访问完入队

    while(front != rear) { //只要队列不空，继续出队
        front = (front + 1) % maxsize;
        j = que[front]; //出队，用j记录出队结点对应数组下标
        p = G->adjlist[v].firstArc; //p指向对应结点的第一条边

        while(p != NULL) {//只要p不为空，循环访问当前v的每一条边
            if(visit[p->adjVex] == 0) {//如果当前边对应的邻接点没有访问过
                Visit(p->adjVex); //访问
                visit[p->adjVex] = 1; //标记访问过
                rear = (rear + 1) % maxsize; //访问后入队
                que[rear] = p->adjVex;
            }
            p = p->nextArc;
        }
    }
}