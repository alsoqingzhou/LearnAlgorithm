#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

typedef struct BTNode{
    char info;
    int data;

    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

void visit(BTNode *bt) {
    cout <<bt->info<<endl;
    return;
}

// Q5.3.3-3 实现后序非递归遍历
// 先序遍历的非递归中，交换左右子树访问顺序得到逆后序，再用一个栈反转得到后序
void postNone(BTNode* bt) {
    // 定义两个栈
    BTNode* stack1[maxsize];
    BTNode* stack2[maxsize];
    int top1 = -1;
    int top2 = -1;

    BTNode *p;

    // 根结点入栈
    stack1[++top1] = bt;

    while(top1 != -1) {
        p = stack1[top1--]; //栈一出栈并访问
        stack2[++top2] = p; //访问完即入栈二

        // 接下来依次访问右孩子与左孩子，故先入栈左孩子
        if(p->lchild != NULL) {
            stack1[++top1] = p->lchild;
        }
        if(p->rchild != NULL) {
            stack1[++top2] = p->rchild;
        }
    }

    // 出栈二并访问得到后序遍历
    while(top2 != -1) {
        p = stack2[top2--];
        visit(p);
    }
}

// Q5.3.3-4 层次遍历从下至上，从右向左
// 基本思想：用循环队列保存正常层次遍历结点，出队后即入栈，然后全部出栈，实现正常层次遍历的反转结果
void reverseLevel(BTNode *bt) {
    BTNode *que[maxsize];
    int front = 0, rear = 0;
    BTNode *q;

    BTNode *stack[maxsize];
    int top = -1;

    if(bt != NULL) {
        rear = (rear+1) % maxsize;
        que[rear] = bt; //根结点入队

        while(front != rear) { //只要队列不空，循环继续
            front = (front + 1) % maxsize;
            q = que[front];
            stack[++top] = q;

            if(q->lchild != NULL) {
                rear = (rear + 1) % maxsize;
                que[rear] = q->lchild;
            }
            if(q->rchild != NULL) {
                rear = (rear + 1) % maxsize;
                que[rear] = q->rchild;
            }
        } //所有结点入栈，跳出循环

        while(top != -1) {
            visit(stack[top--]);
        }
    }
}

// Q5.3.3-5 非递归求二叉树高度
int treeHight(BTNode *bt) {
    int level; //记录二叉树遍历过程的层数

    BTNode *que[maxsize];
    int front = -1, rear = -1; //初始化遍历队列
    int last = 0; //指向每一层最右侧结点指针

    BTNode *p; //用于遍历二叉树

    que[++rear] = bt; //根结点入队

    while(front != rear) {
        p = que[++front];
        if(p->lchild != NULL)  {
            que[++rear] = p->lchild;
        }
        if(p->rchild != NULL) {
            que[++rear] = p->rchild;
        }
        if(front == last) { //到达该层最右端结点
            ++level; //层数加一
            last = rear; //last指向下一层最右端
        }
    }

    return level;
}

// Q5.3.3-6 由中序和先序遍历序列建立二叉链表
// 算法思想：先序第一个元素为根结点，找到其在中序序列中位置，则其中序序列相应位置左右为其左右子树遍历序列，由此确定左右子树范围
// 借助左右子树范围再去对应先序序列找出该段子树的根结点，然后再去对应中序确立左右子树，如此递归求解根结点的左右子树
BTNode* treeCreat(int a[], int b[], int f1, int fn, int m1, int mn) { //依次传入先序，中序遍历数组，先序，中序首尾位置
    BTNode* bt = (BTNode*)malloc(sizeof(BTNode));
    bt->data = a[f1]; //根结点赋值

    int i;
    for(i = m1; b[i] != bt->data; ++i); //遍历中序序列寻找根结点
    // 跳出循环，i为根结点位置
    int left = i - m1; //左子树长度
    int right = mn - i; //右子树长度

    if(left != 0) { //有左子树
        // 传入参数为左子树在先序，中序数组的起始，结束位置
        bt->lchild = treeCreat(a, b, f1+1, f1+left, m1, m1+left-1); //该递归返回左子树中的根结点作为bt的左孩子
    } else {
        bt->lchild = NULL;
    }
    if(right != 0) {
        bt->rchild = treeCreat(a, b, fn-right+1, fn, mn-right+1, mn);
    } else {
        bt->rchild = NULL;
    }
    return bt;
}

// Q5.3.3-7 判定一棵二叉树是否是完全二叉树
// 算法思想：对给定二叉树进行层次遍历，一层层入队，空结点也入队，若出队遇到空结点且其后还有结点，则不是完全二叉树
bool isTotalTree(BTNode *bt) {
    BTNode *queue[maxsize];
    int front = -1, rear = -1;
    BTNode *q; //层次遍历指针

    rear = (rear+1) % maxsize;
    queue[rear] = bt; //根结点入队

    while(front != rear) { //队列不空，一直出队
        front = (front + 1) % maxsize;
        q = queue[front];
        if(q != NULL) { //结点不空，入队其左右孩子
            rear = (rear + 1) % maxsize;
            queue[rear] = q->lchild;
            rear = (rear + 1) % maxsize;
            queue[rear] = q->rchild;
        } else { //q为空结点，检查队列中是否还剩余结点，有剩余则不是完全二叉树
            while(front != rear) {
                front = (front) % maxsize;
                q = queue[front]; //出队
                if(q != NULL) { 
                    return false; //有非空结点，判断为非
                }

            }
        }
    } //跳出循环，完成对二叉树层次遍历
    return true; //经过测验，为完全二叉树
}

// Q5.3.3-8 计算给定二叉树的双分支结点数
// 算法思想：非递归遍历该二叉树，设置计数器，如果左右孩子都不为空，则计数器加一
int tree_n2(BTNode *bt) {
    BTNode* stack[maxsize];
    int top = -1;
    BTNode *p;

    int k; //计数器

    stack[++top] = bt;

    while(top != -1) {
        p = stack[top--];
        if(p->lchild != NULL) {
            stack[++top] = p->lchild;
        }
        if(p->rchild != NULL) {
            stack[++top] = p->rchild;
            ++k;
        }
    }
}