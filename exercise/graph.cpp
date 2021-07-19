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
