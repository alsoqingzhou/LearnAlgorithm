#include <stdio.h>

typedef struct{
    int data[10010];
    int top;
} SqStack;

int a[6] = {1, 2, 3, 4, 5, 6};
SqStack st;

void initStack(SqStack &st) {
    st.top = -1;
}

int main() {
    initStack(st);
    for(int i = 0; i < 6; i++) {
        st.top++;
        st.data[st.top] = a[i];
    }
    int x = st.data[st.top--];
    printf("%d", x);

    return 0;
}
