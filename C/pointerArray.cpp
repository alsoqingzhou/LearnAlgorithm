#include <stdio.h>

int main() {
    int a[10];

    for(int i = 0; i < 6; i++) {
        scanf("%d", a + i);
    }

    for(int i = 0; i < 6; i++) {
        printf("%d", *(a + i));
    }

    return 0;
}