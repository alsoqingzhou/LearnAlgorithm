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