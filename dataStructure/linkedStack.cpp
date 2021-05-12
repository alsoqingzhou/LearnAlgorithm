#include <stdio.h>
#include <malloc.h>

// 不带头结点的链栈基本操作
typedef struct LNode{
    int data;
    struct LNode *next;
}LNode;

//初始化链栈
void init(LNode *&first) {
    first = NULL;
}

int isEmpty(LNode *first) {
    if(first == NULL) {
        return 1; 
    } else {
        return 0;
    }
}

void push(LNode *&first, int x) {
    LNode* s;
    s = (LNode*)malloc(sizeof(LNode));
    s->next = NULL;
    s->data = x;

    s->next = first;
    first = s;
}

int pop(LNode *&first, int &x) {
    LNode *r;
    if(first == NULL) {
        return 0;//此时栈为空
    }
    //若不为空，删除第一个结点
    r = first;//r指向将要删除的结点
    x = r->data;
    first = first->next;//first的下一个结点将成为第一个
    free(r);
    return x;
}