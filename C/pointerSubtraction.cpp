#include <stdio.h>

int main() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7};
    int *p = a;
    int *q = a + 5;

    printf("p = %d\n", p);
    printf("q = %d\n",q);
    printf("q - p = %d\n", q - p);

    return 0;
}