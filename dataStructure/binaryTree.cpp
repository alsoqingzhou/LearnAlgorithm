#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;

// 二叉树结点定义
typedef struct BTNode {
    char data;

    struct BTNode* lchild;
    struct BTNode* rchild;
} BTNode;

void Order(BTNode *p){   
    if(p != NULL) {
        Visit(p); // 先序遍历

        Order(p->lchild);

        Visit(p); // 中序遍历

        Order(p->rchild);

        Visit(p); // 后序遍历
    }
}
void Visit(BTNode* p) {
    printf("%d", p->data);
}

// 利用二叉树计算存储在其中的表达式
int op(int A, int B, char op) {
    if(op = '+') {return A + B;}
    if(op = '-') {return A - B;}
    if(op = '*') {return A * B;}
    if(op = '/') {return A / B;}
}

int compute(BTNode *p) {
    int A, B; //保存左右子树的值
    if(p != NULL) {
        if(p->lchild != NULL && p->rchild != NULL) { 
            //左右子树都存在的结点才访问
            //用A获取左子树数据，B获取右子树数据
            //遍历的每一层A，B都只保存该层结点的孩子数值
            A = compute(p->lchild);
            B = compute(p->rchild);
            return op(A, B, p->data);//集齐A，B返回compute函数运算结果
        } else {
            // 处理叶子结点
            return p->data - '0'; //叶子结点必为数值，返回字符转换后数值
        }
    } else { //二叉树为空树 
        return 0;
    }
}

// 求二叉树深度
// 基本思想：获取左子树和右子树深度，则该树深度为两者中较大的加一
// 递归结束条件：到达叶子结点，则叶子结点的左右子树为空，返回得到叶子结点（作为一个独立的树时）深度为一
int getDepth(BTNode *p) {
    int left, right;
    if(p == NULL) {
        return 0; //叶子结点的左右子树为空，空树深度为一
    } else {
        left = getDepth(p->lchild);
        right = getDepth(p->rchild);
        return max(left, right) + 1;
    }
}

// 二叉树查找值为key的结点是否存在
void search(BTNode *p, BTNode *&q, int key) {
    if(p != NULL) {
        if(p->data == key) { // 到达结点后先对该结点数据进行访问判断，故采用的先序遍历
            q = p;
        } else {
            search(p->lchild, q, key);
            search(p->rchild, q, key);
        }
    }
}

// 剪枝操作优化上述搜索代码
void search2(BTNode *p, BTNode *&q, int key) {
    if(p != NULL) {
        if(p->data == key) {
            q = p;
        } else {
            search2(p->lchild, q, key);
            if(q == NULL) { //左子树如果没有找到，才会搜索右子树
                search2(p->rchild, q, key);
            }
        }
    }
}

// 输出先序遍历第k个结点的值
// 计数i应放在函数体外作为全局变量
int i = 1; //用于计数访问到第几个结点

void printK(BTNode *p, int k) {
    // 初始p指向根结点，即访问到序列第一个结点
    if(p != NULL) {
        if(i == k) {
            cout << p->data<<endl;
            return;
        } else {
            ++i; // 将访问下一个结点，计数加一
            printK(p->lchild, k);
            printK(p->rchild, k);
        }
    }
}

// 为构造不同顺序遍历的模板，换种写法
int n = 0; //注意是访问计数器，不是遍历结点计数器，没有访问结点之前为0
// 这样对所有顺序访问都是公平的
// 上面写法计数器初始值为1，有默认遍历到第一个结点即访问，默认了先序遍历
void printFun(BTNode *p, int k) {
    if(p != NULL) {
        //下面这部分即访问代码
        ++n;//准备访问当前p遍历指向的结点，计数器加一
        if(k == n) {
            //如果是访问的第k个，满足条件打印
            cout <<p->data<<endl;
            return; //跳出递归
        }
        // 访问代码到此结束

        // 如果是中序，后序，将上面几行代码放到下面两行中间，末尾
        printFun(p->lchild, k);
        // 放这里中序遍历
        printFun(p->rchild, k);
        // 放这里后序遍历
    }
}

// 层次遍历
int const maxsize = 10010;
void level(BTNode *p) {
    // 先创建一个队列用于从左向右保存每一层的结点值
    int front, rear;
    BTNode *que[maxsize]; //该数组构建循环队列，其中保存的是结点的指针
    front = rear = 0;
    BTNode *q; // 该二叉树指针指向将要出队的元素

    // 开始层次遍历
    if(p != NULL) { //只要不是空结点，就要入队出队遍历
        rear = (rear+1) % maxsize;
        que[rear] = p; //p为根节点，此时根节点入队
        while(front != rear) {// 只要队列不空，循环继续
            front = (front + 1) % maxsize;//队首出队
            q = que[front];
            Visit(q);

            if(q->lchild != NULL) { //有左孩子，左孩子入队
                rear = (rear + 1) % maxsize;
                que[rear] = q->lchild;
            }
            if(q->rchild != NULL) { //有右孩子，右孩子入队
                rear = (rear + 1) % maxsize;
                que[rear] = q->rchild;
            }

        }
    }
}

// 层次遍历求二叉树最大宽度
typedef struct {
    BTNode *p; //指向二叉树的结点的指针
    int level; //保存结点的层数
} queue;

int maxWidth(BTNode *r) { //传入二叉树根节点
    // 利用新定义的结构体初始化用于保存遍历结果的队列,采用结构体数组
    queue que[maxsize];
    int front, rear;
    front = rear = 0;

    int levNum = 0;
    BTNode *s; //指向当前出队的结点的指针
    if(r != NULL) {
        // 根节点入队
        ++rear; //假设队列长度足够，不采用循环队列
        que[rear].p = r;
        que[rear].level = 1; //根结点层数为1
        
        while(front != rear) {//队列未出队完成，循环继续
            ++front; //根节点出队，注意只是访问，没有删除
            s = que[front].p; //访问目的一，获取当前结点指针
            levNum = que[front].level; //访问目的二，获取当前结点层数，以便给孩子层数赋值
            
            if(s->lchild != NULL) {
                ++rear;
                que[rear].p = s->lchild;
                que[rear].level = levNum + 1;
            }
            if(s->rchild != NULL) {
                ++rear;
                que[rear].p = s->rchild;
                que[rear].level = levNum + 1;
            }
        } // 循环结束，所有结点都保存在que数组中
        // 开始找最大层数
        int max = 0;
        for(int i = 1; i <= levNum; ++i) { //循环每一层
            int n = 0; //临时保存当前层的节点数
            for(int j = 1; j <= rear; ++j) {
                //该层循环从队首开始，一直走到队尾、
                // 由于不知道每一层有多少个结点，因此只能遍历整个队列，确定是不是当前层的结点
                if(que[j].level == i) { // 如果是当前层的
                    ++n; //当前层结点数加一
                }
                if(n > max) {//如果当前层结点数超过目前确认的最大值，更新最大值
                    max = n;
                }
            }
        }
        return max;
    } else { //二叉树为空，返回宽度0
        return 0;
    }
}