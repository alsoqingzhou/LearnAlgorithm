#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

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