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