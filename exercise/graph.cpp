#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

//Q6.2.6-4 图的邻接表转换为邻接矩阵

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
