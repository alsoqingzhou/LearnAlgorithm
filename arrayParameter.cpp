#include <stdio.h>

void change(int a[], int b[][5]) {
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    b[0][0] = 6;
}

int main() {
    int a[3] = {0, 0, 0};
    int b[5][5] = {1, 2};
    // change(a, b);
    for(int i = 0; i < 4; i++) {
        printf("%d\n", a[i]);
    }
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            printf("%d", b[i][j]);
        }
        printf("\n");
    }

    return 0;
}