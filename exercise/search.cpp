#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

// Q7.2.4-6 折半查找的递归实现
typedef struct {
    int *a;
    int length;
} SSTable;

int biSearch_recursive(SSTable st, int low, int high, int key) {
    while(low < high) {
        int mid = (low + high) / 2;
        if(st.a[mid] == key) {
            return mid;
        } else if(st.a[mid] < key) { //对左边二分查找
            biSearch_recursive(st, low, mid-1, key);
        } else { //对右边二分查找
            biSearch_recursive(st, mid+1, high, key);
        }
    }
    return 0; //跳出循环，查找失败
}

// 线性表顺序检索算法优化：将每次查找到的元素提前一位
// Q7.2.4
typedef struct linkList {
    int data;
    struct linkList *next;
} linkList; //顺序表的单链表存储

int seqSearch(SSTable &st, int key) {
    int i;
    for(i = 0; i < st.length; ++i) {
        if(st.a[i] == key) {
            int temp = st.a[i];
            st.a[i] = st.a[i-1];
            st.a[i-1] = temp;
            return i-1;
        }
    }
    if(i >= st.length) {
        return 0;
    }
}

int linkSearch(linkList* l, int key) {
    linkList *p, *q, *r;
    p = l;
    while(p->next->next != NULL) {
        if(p->next->next->data == key) {
            q = p->next;
            r = q->next->next;
            q->next = r->next;
            r->next = q;
            p->next = r;
            return 1;
        }
    }
    if(l->next->data == key && l->next->next == NULL) {
        return 1; //该单链表只有一个元素，就是第一个
    } else {
        return 0;
    }
}
