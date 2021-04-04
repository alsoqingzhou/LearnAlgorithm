#include <stdio.h>

void change(int &x) {
    x = 6;
}

int main() {
    int a = 1;
    change(a);
    printf("%d", a);

    return 0;
}