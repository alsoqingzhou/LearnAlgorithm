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