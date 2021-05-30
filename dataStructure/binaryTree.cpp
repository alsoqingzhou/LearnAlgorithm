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