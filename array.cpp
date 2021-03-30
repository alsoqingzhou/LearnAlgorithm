#include <stdio.h>
int main() {
    int a[10] = {5, 3, 4, 7, 8}; // other a[] will be 0
    for (int i = 0; i < 10; i++)
    {
        printf("a[%d] = %d\n", i, a[i]);
    }
    return 0;
}