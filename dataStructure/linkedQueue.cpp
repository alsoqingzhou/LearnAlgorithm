#include <malloc.h>
#include <stdio.h>

//定义链队结点
//队中结点定义
typedef struct QNode {
    int data;
    struct QNode *next;
}QNode;

//队首队尾指针即链队类型定义
typedef struct {
    QNode *front;
    QNode *rear;
}LiQueue;

//init linked queue
void init(LiQueue *&liq) {
    liq = (LiQueue*)malloc(sizeof(LiQueue));
    liq->front = NULL;
    liq->rear = NULL;
}

//is empty
int isEmpty(LiQueue *liq) {
    if(liq->front == NULL || liq->rear == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//enter
void enLiQueue(LiQueue *liq, int x) {//假设内存无限大
    QNode *p;
    p = (QNode*)malloc(sizeof(QNode));
    p->data = x;
    p->next = NULL;

    if(liq->rear == NULL) {//链队第一个结点特殊处理
        liq->rear = p;
        liq->front = p;
    } else {
        liq->rear->next = p;
        liq->rear = p;
    }
}
    

//delete
int deLiQueue(LiQueue *liq, int &x) {
    if(liq->rear == NULL) {//链队为空，无法删除
        return 0;
    }
    //start deleting
    QNode *p;
    p = liq->front;
    x = p->data;

    if(liq->front == liq->rear) {//只剩一个结点，特殊处理
        liq->front = liq->rear = NULL;
    } else {
        liq->front = p->next;
        free(p);
    }
    return 1;
}
