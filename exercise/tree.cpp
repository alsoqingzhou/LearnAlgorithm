#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

typedef struct BTNode{
    char info;

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