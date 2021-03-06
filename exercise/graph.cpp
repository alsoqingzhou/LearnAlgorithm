#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;


// 首先是图的邻接表结构体定义
typedef struct ArcNode{
    int adjVex; //边对应结点
    ArcNode *nextArc; //边指针，指向下一条边
} ArcNode; //边表结点
typedef struct {
    int data; //顶点信息
    ArcNode *firstArc; //边指针，指向第一条边
} VNode; //顶点表结点
typedef struct {
    int n, e; //图中结点数，边数
    VNode adjList[maxsize]; //顶点结点数组
} AGraph; //图的邻接表定义

// 图的邻接矩阵定义（简略形式，只保存边信息
typedef struct {
    int n, e; //图的结点和边数
    int edges[maxsize][maxsize];
} MGraph; //图的邻接矩阵定义

// 访问图的结点
void Visit(VNode p) {
    cout<<p.data<<endl;
}

// 在递归过程中，visit数组应为全局变量
int visit[maxsize];

//Q6.2.6-4 图的邻接表转换为邻接矩阵
void trans(AGraph *g, MGraph *ng) {
    ArcNode *p; //用于遍历每条边的指针
    for(int i = 1; i <= g->n; ++i) { //循环遍历每一个顶点
        p = g->adjList[i].firstArc;
        while(p != NULL) { //循环遍历当前顶点的每一条边
            ng->edges[i][p->adjVex] = 1; //从当前顶点出发有边到相邻顶点，则邻接矩阵对应位置标记
            p = p->nextArc;
        }
    }
}

// Q6.3.4-2 判断一个无向图是否为一棵树
// 基本思想，判断一个无向图是否是连通图且边数只有n-1条
// 判断是否连通，采用一次遍历结点并计数,图采用邻接表存储
void DFS(AGraph *g, int &vNum, int &eNum, int visit[], int v) { //传入图，结点和边计数，访问数组和第一个结点
    visit[v] = 1;
    ++vNum; //结点计数加一
    ArcNode *p;
    p = g->adjList[v].firstArc;
    while(p != NULL) {
        ++eNum; //边存在，边计数
        if(visit[p->adjVex] == 0) { //边对应结点没有被访问过
            DFS(g, vNum, eNum, visit, p->adjVex);
        }
        p = p->nextArc; //指向下一条边
    }
}
bool isTree(AGraph *g) {
    int visit[maxsize];
    for(int i = 0; i < g->n; ++i) {
        visit[i] = 0; //访问数组初始化
    }
    int vNum = 0, eNum = 0; //结点与边计数初始化
    DFS(g, vNum, eNum, visit, 0);
    if(vNum == g->n && eNum == 2*(g->n - 1)) {
        return true;
    } else {
        return false;
    }
}

// Q6.3.4-3 邻接表存储的图的深度优先搜索非递归算法
void DFSNoneRecursion(AGraph *g, int visit[], int v) {
    for(int i = 0; i < g->n; ++i) {
        visit[i] = 0;
    } //初始化访问数组
    ArcNode* p; //用于遍历图中边
    int stack[maxsize]; //保存要访问的顶点编号
    int top = -1;

    stack[++top] = v; //传入结点入栈
    visit[v] = 1; //入栈即标记访问，避免再次入栈

    while(top != -1) {
        int r = stack[top--]; //栈顶出栈
        Visit(g->adjList[r]); //访问栈顶对应结点

        p = g->adjList[r].firstArc; //边指针指向结点的第一条边
        while(p != NULL) {
            if(visit[p->adjVex] == 0) {
                stack[++top] = p->adjVex;
                visit[p->adjVex] = 1;
                
                p = p->nextArc;
            }
        }
    }
}

// Q6.3.4-4 基于DFS和BFS确定用邻接表存储的图中是否有vi到vj的路径，i!=j
// 算法思想：广度优先，从i结点开始，每次结点出队时检查是否为j
int BFSi_j(AGraph *g, int i, int j) {
    // 初始化队列，访问数组，遍历指针
    int que[maxsize]; int front = -1, rear = -1;
    int visit[maxsize];
    for(int i = 0; i < g->n; ++i) {
        visit[i] = 0;
    }
    ArcNode *p; //遍历边的指针
    int q; //队列指针

    // 结点i入队
    que[++rear] = i;
    visit[i] = 1;

    while(front != rear) {
        q = que[++front];
        if(q == j) { //遍历到j,说明有路径
            return  1;
        }
        p = g->adjList[q].firstArc;
        while(p != NULL) {
            if(visit[p->adjVex] == 0) {
                que[++rear] = p->adjVex;
                visit[p->adjVex] = 1;
            }
            p = p->nextArc;
        }
    }
    // 遍历完成，没有找到j,没有路径
    return 0;
}

// 深度优先
// 算法思想：深度优先搜索过程中，顺带上目标结点的位置，以及判断符，如果遍历到目标结点，说明有路径，从递归中返回
int DFSi_j(AGraph *g, int i, int j, bool &path) {
    ArcNode *p;

    visit[i] = 1;
    if(i == j) {
        path = true;
        return 1;
    }

    p = g->adjList[i].firstArc;
    while(p != NULL) {
        if(visit[p->adjVex] == 0 && !path) { //找到路径后依然会遍历完当前结点每一条边才会结束
            // 用path可以控制找到路径后不再进入递归
            DFSi_j(g, p->adjVex, j, path);
        }
        p = p->nextArc;
    }
}

// Q6.3.4-5 输出邻接表表示的图中从i到j所有简单路径
// 算法思想：从i开始对图深度优先遍历，设置路径数组，每深度遍历到一个未访问结点，依次添加进路径数组
// 每一次深度遍历找到j,就打印出路径，退出该层递归前消除对当前访问结点的访问痕迹，以便在下一条不同路径时利用该结点
void graph_i_j(AGraph *g, int i, int j, int path[], int k) { //k未路径结点数计数器，或成为结点的路径数组指针
    ArcNode *p; //辅助边指针

    ++k; //路径数组入当前访问结点i
    path[k] = i;
    visit[i] = 1;

    if(i = j) {
        //深度遍历到目标结点，打印路径数组
    } else { //没有找到，继续遍历
        p = g->adjList[i].firstArc;
        while(p != NULL) {
            if(visit[p->adjVex] == 0) {
                graph_i_j(g, i, j, path, k);
                p = p->nextArc;
            }
        }
    }
    // 打印出一条路径，当前访问结点清除访问记录
    visit[i] = 0;
}