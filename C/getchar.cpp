#include <stdio.h>
int main() {
    char c1, c2, c3;
    c1 = getchar();
    getchar(); // this input will not be shown
    c2 = getchar();
    c3 = getchar();
    putchar(c1);
    putchar(c2);
    putchar(c3);
    return 0;
}