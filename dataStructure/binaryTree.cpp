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