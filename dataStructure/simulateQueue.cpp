#include <stdio.h>

int const maxsize = 10010;

int a[6] = {1, 2, 3, 4, 5, 6};

typedef struct {
    int data[6];
    int top;
}SqStack;

void initStack(SqStack &st) {
    st.top = -1;
    for(int i = 0; i < 6; i++) {
        st.data[++st.top] = a[i];
    }
}

SqStack s1, s2;

int push(SqStack &st, int x) {//push into s1 to simulate enter queue
    if(st.top == maxsize - 1) {//stack is full
        return 0;
    }
    ++st.top;
    st.data[st.top] = x;
    return 1;
}

int pop(SqStack &st, int x) {
    if(st.top == -1) {
        return 0;//stack is empty
    }
    x = st.data[st.top];
    --st.top;
    return 1;
}

bool isEmpty(SqStack &st) {
    if(st.top == -1) {
        return true;
    } else {
        return false;
    }
}

int enQueue(int x) {
    int y;//接收从s1出栈再向s2入栈的值
    if(s1.top == maxsize - 1) {//s1 is full, see if s2 is empty
        if(!isEmpty(s2)) {// s2 is full, cannot enter
            return 0;
        } else {//将s1全部出栈到s2,然后s1再进栈
            while(!isEmpty(s1)) {//只要s1没有出光，继续出
                pop(s1, y);
                push(s2, y);
            }
            push(s1, x);
            return 1;
        }
    } else {//s1 is not full, just enter
        push(s1, x);
        return 1;
    }
}

int deQueue(int x) {
    int y;
    if(!isEmpty(s2)) {//s2 is not empty, just delete
        pop(s2, x);
        return 1;
    } else {//s2 is empty, see if s1 is empty
        if(isEmpty(s1)) {
            return 0;//both empty, nothing to delete
        } else {
            while(!isEmpty(s1)) {
                pop(s1, y);
                push(s2, y);
            }
            pop(s2, x);
            return 1;
        }
    }
}

bool isQueueEmpty() {
    if(isEmpty(s1) && isEmpty(s2)) {
        return true;
    } else return false;
}

int main() {
    initStack(s1);
    s2.top = -1;
    // printf("%d", isEmpty(s1));
    int x1, x2, x3, x4, x5, x6;
    deQueue(x1);
    deQueue(x2);
    deQueue(x3);
    deQueue(x4);
    printf("%d",x4);
    return 0;
}