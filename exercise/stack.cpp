#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

// 单链表结构体定义
typedef struct LinkList{
    char data;
    LinkList *next;
} LinkList;

//Q3.1.4-3
bool justify(char a[], int n) {
    char stack[maxsize], top = -1;
    
    //将输入序列中字符依次循环处理，如果为I就入栈，如果为O就出栈
    for(int i = 0; i < n; ++i) {
        if(a[i] == 'I') {
            stack[++top] = 'I';
        }
        if(a[i] = 'O') {
            if(top == -1) {
                return false;
            } else {
                --top;
            }
        }
    }

    if(top == -1) return true;
    else return false;
}

// Q3.1.4-4
int IsSymmetry(LinkList *l, int n) { //传入参数为单链表头结点和链表长度
    char stack[maxsize];
    int top = -1;

    LinkList *p;
    p = l->next;

    for(int i = 0; i < n/2; ++i) {
        stack[++top] = p->data;
        p = p->next;
    }

    if(n % 2 == 1) { //表长为奇数，跳过中间结点
        p = p->next; //此时p指向中心对称的后半部分
    }

    while(p != NULL) {
        if(p->data != stack[top]) {
            return 0;
        }
        p = p->next;
        --top;
    }
    //走出循环，说明中心对称
    return 1;
}

// Q3.1.4-5 实现共享栈
// 算法思想：两个栈共享一片连续空间，两个栈栈顶位于两端，栈顶相对
typedef struct {
    int elem[maxsize];
    int top[2];
} shareStack;
shareStack st;

int push(int stNum, int x) {
    // 首先判断栈是否已满
    if(st.top[1] - st.top[0] == 1)  {
        return 0; //stack is full
    }
    switch(stNum) {
        case 0: st.elem[++st.top[0]] = x; return 1; break;
        case 1: st.elem[++st.top[1]] = x; return 1;
    }
}

int pop(int stNum) {
    switch(stNum) {
        case 0: {
            if(st.top[0] == -1) {
                return 0; //stack 1 is empty
            } else {
                return st.elem[st.top[0]++];
            }
        }
        case 1: {
            if(st.top[1] == maxsize) {
                return 0; //stack 2 is empty
            } else {
                return st.elem[st.top[1]++];
            }
        }
    }
}

// Q3.2.5-1 循环队列利用标记位区分队空和队满，出队，入队算法
// 队列结构体定义
typedef struct{
    int data[maxsize];
    int front, rear;
    int tag; //队空队满标记符，完成进队后重置为1，完成出队后重置为0
} queue;
void initQueue(queue &q) {
    q.front = q.rear = 0;
    q.tag = 0;//初始化队为空，类似刚出完队，故tag置0
}

bool enterQueue(queue &q, int x) {
    if(q.front == q.rear && q.tag == 1) {
        //tag为1说明前一次是入队，导致首尾相同，此时队满
        return false; //入队失败
    }
    q.rear = (q.rear + 1) % maxsize;
    q.data[q.rear] = x;
    q.tag = 1; //入队完成置1
    return true;
}
bool deleteQueue(queue &q, int x) {
    if(q.front == q.rear && q.tag == 0) {
        // tag为0，前一次出队导致的首尾相同，此时队空
        return false;
    }
    q.front = (q.front + 1) % maxsize;
    x = q.data[q.front];
    q.tag = 0;
    return true;
}
