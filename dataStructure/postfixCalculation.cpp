#include <iostream>
#include <stdio.h>
using namespace std;

int operation(int a, char op, int b) {
    if(op == '+') {
        return a + b;
    }
    if(op == '-') {
        return a - b;
    }
    if(op == '*') {
        return a * b;
    }
    if(op == '/') {
        if(b == 0) {
            cout << "ERROR" <<endl;
            return 0;
        } else {
            return a / b;
        }
    }
}

int cal(char exp[]) {
    int a, b, c;
    char op;
    int stack[10];
    int top = -1;

    for(int i = 0; exp[i] != '\0'; ++i) {
        if(exp[i] >= '0' && exp[i] <= '9') {//字符为数字
            stack[++top] = exp[i] - '0';//计算字符串的相对位置得到对应数值，压入栈
        } else {//遇到运算符
            op = exp[i];//op获取运算符
            b = stack[top--];//先出栈的为b
            a = stack[top--];
            c = operation(a, op, b);//c保存运算结果并入栈
            stack[++top] = c;
        }
    }

    return stack[top];
}

int main() {
    char exp[9] = {'1', '2', '3', '4', '*', '+', '+', '2', '/'};
    int x = cal(exp);
    printf("%d", x);
    return 0;
}