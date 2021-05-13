#include <stdio.h>

int const maxsize = 10010;

typedef struct {
    int data[maxsize];
    int top;
} stack;

stack s0, s1;

void initS0(stack &st) {
    st.top = -1;
}

void initS1(stack &st) {
    st.top = maxsize;
}

int pushS0(stack &st, int x) {
    if(st.top + 1 == s1.top) {//the stack is full
        return 0;
    }
    ++st.top;
    st.data[st.top] = x;
    return 1;
}

int pushS1(stack &st, int x) {
    if(st.top - 1 == s0.top) {
        return 0;
    }
    --st.top;
    st.data[st.top] = x;
    return 1;
}

int popS0(stack &st, int x) {
    if(st.top == -1) {//the stack is empty
        return 0;
    }
    x = st.data[st.top];
    --st.top;
    return 1;
}

int popS1(stack &st, int x) {
    if(st.top == maxsize) {
        return 0;
    }
    x = st.data[st.top];
    ++st.top;
    return 1;
}

// 下面是合并写法
typedef struct {
    int elem[maxsize];
    int top[2];
    //top[0] is the top of s0
    //top[1] is the top of s1
} SqStack;

int push(SqStack &st, int stNum, int x) {//stNum decide which stack will be pushed
    if(st.top[0] + 1 == st.top[1]) {//the stack is full
        return 0;
    }
    if(stNum == 0) {
        ++st.top[0];
        st.elem[st.top[0]] = x;
        return 1;
    }
    if(stNum == 1) {
        ++st.top[1];
        st.elem[st.top[1]] = x;
        return 1;
    }
}

int pop(SqStack &st, int stNum, int x) {
    if(stNum == 0) {
        if(st.top[0] = -1)  {//s0 is empty
            return 0;
        }
        x = st.elem[st.top[0]];
        --st.top[0];
        return 1;
    }
    if(stNum == 1) {
        if(st.top[1] = maxsize) {//s1 is empty
            return 0;
        }
        x = st.elem[st.top[1]];
        ++st.top[1];
        return 1;
    }
}