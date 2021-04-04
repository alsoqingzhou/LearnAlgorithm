#include <stdio.h>

void change(int *p) {
    *p = 6;
}

int main() {
    int a = 1;
    int *p = &a;
    change(p);
    printf("%d", a);
}