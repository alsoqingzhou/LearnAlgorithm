#include <iostream>
#include <malloc.h>
using namespace std;

//双链表结点定义
typedef struct DLNode {
    int data;
    struct DLNode *prior;
    struct DLNode *next;
}DLNode;

DLNode *L; //定义结点指针变量L

//尾插法建立双链表
// DLNode* createDlist(DLNode *&L, int a[], int n) {
//     DLNode *r, *s;//r指向尾结点，s指向新结点
//     L = (DLNode*)malloc(sizeof(DLNode));
//     L->prior = NULL;//初始化结点
//     L->next = NULL;
//     r = L;//此时只有L结点，即尾结点

//     for(int i = 0; i < n; i++) {
//         s = (DLNode*)malloc(sizeof(DLNode));
//         s->data = a[i];
//         r->next = s;//s接上链表
//         s->prior = r;
//         r = s;
//     }
//     //全部数组元素获取完毕，跳出循环
//     r->next = NULL;//尾结点下一个为空
//     //如果创建循环双链表，跳出循环后是下面两句
//     // r->next = L;//尾结点之后指向头结点
//     // L->prior = r;//头结点之前指向尾结点

//     return L;
// }

//头插法建立双链表
DLNode* createDList(DLNode *&L, int a[], int n) {
    DLNode *r, *s;
    L = (DLNode*)malloc(sizeof(DLNode));
    L->prior = NULL;
    L->next = NULL;
    r = L;

    for(int i = 0; i < n; i++) {
        if(r->prior == NULL) { //第一个新结点特殊操作
            s = (DLNode*)malloc(sizeof(DLNode));
            s->data = a[i];
            s->prior = r;
            s->next = NULL;
            r->next = s;
            r = s;
        } else{
            s = (DLNode*)malloc(sizeof(DLNode));
            s->data = a[i];
            s->prior = r->prior;
            r->prior = s;
            s->prior->next = s;
            s->next = r;
            r = s;
        }
    }

    return L;
}

//查找结点并删除，返回删除结点的值
int Delete(DLNode *L, int x) {
    DLNode *f, *q;
    f = L;
    int val;
    //查找开始
    while(f->next != NULL) {//为到达表尾，继续查找
        if(f->next->data == x) {
            val = f->next->data;
            break; //找到，跳出循环
        } else {
            f = f->next;
        }
    }
    if(f->next == NULL) {
        return 0;
    }

    //删除结点
    q = f->next;
    q->next->prior = f;
    f->next = q->next;
    free(q);
    
    return val;
}

int main() {
    int a[6] = {1, 2, 3, 4, 5, 6};
    DLNode *p = createDList(L, a, 6);
    DLNode *o = p;//用于删除结点后再次输出链表

    while(p->next != NULL) {
        printf("%d", p->next->data);
        p = p->next;
    }
    //删除结点并返回值
    int x = Delete(L, 3);
    printf("\n%d\n", x);

    while(o->next != NULL) {
        printf("%d", o->next->data);
        o = o->next;
    }
    return 0;
}

