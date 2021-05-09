#include <stdio.h>

int match(char exp[], int n) {
    char stack[10010]; int top = -1;

    for(int i = 0; i < n; ++i) {
        if(exp[i] == '(') {
            stack[++top] = '(';
        }
        if(exp[i] == ')') {
            if(top == -1) {
                return 0;
            } else {
                --top;
            }
        }
    }

    if(top == -1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char exp[10] = {'(', '(', ')', ')'};
    printf("%d", match(exp, 10));

    return 0;
}