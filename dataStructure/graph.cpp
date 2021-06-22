#include <stdio.h>
const int maxsize = 10010;
const int IFN = 100;

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
    int que[maxsize], front = 0, rear = 0; //定义队列，依次入队某个结点未访问的邻接点
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

// Prim算法得到图的最小生成树
void prim(MGraph g, int v0, int &sum) {
    int lowCost[maxsize]; //权值数组，记录当前生成树到图中各结点边的距离
    int vset[maxsize]; //处理标记数组，记录图中结点是否并入树中
    int min; //记录更新的权值数组中最小值
    int k; //记录权值数组中最小值对应的结点
    int v; //记录刚并入树的结点

    // 处理初始结点v0
    v = v0; //初始结点入树
    vset[v0] = 1;
    sum = 0; //单结点树没有边，权值为0
    
    // 辅助数组初始化
    for(int i = 0; i < g.n; ++i) {
        lowCost[i] = g.edges[v0][i]; //当前各结点最小权值即初始结点v0到i的边权值
        vset[i] = 0; //各结点均没有并入生成树，此时为空树
    }

    //最外层循环，共n-1次，处理初始结点外的剩余结点
    for(int i = 0; i < g.n-1; ++i) {

        //首先找出到树的边中权值最小的，并入当前最小生成树
        //意味着循环遍历最新的权值数组，确定其中的最小值min
        min = IFN; //初始最小值IFN，准备更新
        for(int j = 0; j < g.n; ++j) {
            //理想结点既没有并入生成树中，同时还是最小值，满足以上两个条件
            if(vset[j] == 0 && lowCost[j] < min) {
                min = lowCost[j];
                k = j;
            }
        } //跳出循环，此时min对应权值数组中最小值，k指向对应结点

        vset[k] = 1; //并入生成树中
        v = k; //标记新并入结点
        sum += min;

        // 更新权值数组
        for(int j = 0; j < g.n; j++) {
            //对这样的结点对应的权值数组值进行更新
            // 既没有并入生成树中
            // 同时满足上面新入树的结点v到遍历到的结点j的边的距离小于生成树到结点j的距离
            if(vset[j] == 0 && g.edges[v][j] < lowCost[j]) {
                lowCost[j] = g.edges[v][j];
            }
        }
    }
}


/*Kruskal算法*/
typedef struct { // 定义图的边存储方式的结构体
    int a, b; //构成一条边的两个结点
    int w; //边的权重
} Rood;

Rood rood[maxsize]; //Rood结构体数组
int v[maxsize]; //并查集数组,输入结点，输出父结点

int getRoot(int p) {
    while(p != v[p]) { //父结点不是自身，即没有找到根结点，继续
        p = v[p]; //p指向其父结点
    }
    return p; //找到根结点，返回
}

void sort(Rood rood[], AGraph g) {
    //根据边的权值升序
}

void Kruskal(AGraph g, Rood rood[], int &sum) {
    sum = 0; //最小生成树权值累加

    //并查集初始化
    for(int i = 0; i < g.n; ++i) {
        v[i] = i; //此时每个结点都是根结点
    }

    sort(rood, g);

    // 对图中的所有边循环
    for(int i = 0; i < g.e; ++i) {
        int a = getRoot(rood[i].a); //边i一端的结点的根结点
        int b = getRoot(rood[i].b); //边i另一端的结点的根结点

        if(a != b) { //根结点不同，两个结点不在同一棵树
            v[a] = b; //并查集上合并a和b所在的两棵树
            sum += rood[i].w; //生成树权值累加
        }
    }
}

/*Dijkstra 算法*/
void Dijkstra(MGraph g, int v, int path[], int Dist[]) { //传入参数有图以及开始结点
    // int Dist[maxsize]; //当前从开始顶点到图中其余顶点的最短距离长度
    // int path[maxsize]; //最短路径上结点的前驱
    int set[maxsize]; //标记结点是否并入最短路径

    // 初始化
    for(int i = 0; i < g.n; ++i) {
        Dist[i] = g.edges[v][i]; //dist初始化为v到各边的距离
        set[i] = 0;
        if(g.edges[v][i] < IFN) {
            path[i] = v;
        } else {
            path[i] = -1;
        }
    }

    for(int i = 0; i < g.n-1; ++i) { //该层循环对除开始结点外所有结点循环，并入最短路径
        int min = IFN; //记录最短路径的距离
        int u; //记录刚并入最短路径的结点

        for(int j = 0; j < g.n; ++j) { //该层循环找出当前没有并入最短路径的剩余结点中距离最短的
            if(set[i] == 0 && Dist[i] < min) {
                min = Dist[i];
                u = j;
            }
        }
        set[u] = 1; //将选出的结点并入最短路径

        for(int j = 0; j < g.n; ++j) { //该层循环根据新并入结点得到最短路径更新Dist,并确定path
            if(set[j] == 0 && Dist[u] + g.edges[u][j] < Dist[j]) { //通过新并入结点到达j的路径小于不通过其到达j的路径长度
                Dist[j] = Dist[u] + g.edges[u][j];
                path[j] = u;
            }
        }
    }
}

// Floyd 算法求图中任意两点之间最短路径
void Floyd(MGraph g, int Path[][maxsize], int A[][maxsize]) {
    // 初始化
    for(int i = 0; i < g.n; ++i) {
        for(int j = 0; j < g.n; ++j) {
            Path[i][j] = -1;  //path初始化为-1，表示任意两个结点之间没有中间点
            A[i][j] = g.edges[i][j]; //A初始化为邻接矩阵的边权值，用于保存两结点之间最短路径长度
        }
    }

    for(int k = 0; k < g.n; ++k) { //该层循环选取每个结点为中间点
        for(int i = 0; i < g.n; ++i) { //该层循环与下一层遍历图中每一对边
            for(int j = 0; j < g.n; ++j) {
                if(A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j]; //经过中间点的路径更短，更新i与j之间路径距离
                    Path[i][j] = k; //i与j之间中间点为k
                }
            }
        }
    }
}
//输出从结点u到结点v的最短路径
void printPath(int Path[][maxsize], int u, int v) {
    if(Path[u][v] = -1) { //两结点之间没有中间点
        // 直接输出
    } else {
        mid = Path[u][v];
        printPath(u, mid, Path); //递归输出起点到中间点的最短路径
        printPath(mid, v, Path); //递归输出中间点到终点的最短路径
    }
}