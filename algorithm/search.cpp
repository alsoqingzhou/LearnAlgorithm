#include <stdio.h>
#include <iostream>
using namespace std;

int a[10] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// 顺序查找
typedef struct {
    int *elem; //动态分配的顺序表的开始指针
    int TableLen; //保存顺序表的长度
} SeqList;

// 利用哨兵提高查找效率，找到及时停止
int Search(SeqList L, int key) {
    int i;
    L.elem[0] = key; //顺序表0位置不保存信息，留给安放待查找的哨兵
    //重点在于下面的for循环，用于移动指针，
    for(i = L.TableLen-1; L.elem[i] != key; --i);
    //若找到key,则跳出循环，i即key的位置
    //若没有找到key, 则循环到0位置遇到哨兵退出循环，返回0，表示查找失败
    return i;
}

// 折半查找
int BinarySearch(int a[], int low, int high, int key) {
    int mid;
    while(low <= high) {
        mid = (low + high) / 2;
        if(a[mid] == key) {
            return mid;
        } else if(a[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    // 跳出循环，查找失败
    return 0;
}

// 二叉查找树
typedef struct BTNode {
    int key;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode;

//非递归方式查找
BTNode* BTSearch(BTNode* t, int key) {
    while(t != NULL && t->key != key) {
        if(t->key < key) {
            t = t->lchild;
        } else {
            t = t->rchild;
        }
    }

    return t; //成功返回结点指针t,失败返回null
}

// 递归方式查找二叉平衡树
BTNode* BTDSearch(BTNode* t, int key) {
    if(t == NULL) {return NULL;}

    if(t->key == key) {
        return t;
    } else if(t->key < key) {
        return BTDSearch(t->lchild, key); //下一层递归函数从这里返回上来
    } else {
        return BTDSearch(t->rchild, key);
    }
}

// 递归实现二叉平衡树插入
int add(BTNode *&t, int key) {
    if(t == NULL) {
        t = (BTNode*)malloc(sizeof(BTNode));
        t->key = key;
        t->lchild = t->rchild = NULL;
        return 1; //插入成功
    }
    if(t->key = key) {
        return 0; //值已存在，插入失败
    } else if(t->key < key) {
        return add(t->lchild, key); //返回左孩子这边是否插入成功
    } else {
        return add(t->rchild, key); //返回右孩子是否插入成功
    }
}

int main() {
    int key = 6;
    int x = BinarySearch(a, 1, 9, 6);
    printf("%d", x);
    return 0;
}