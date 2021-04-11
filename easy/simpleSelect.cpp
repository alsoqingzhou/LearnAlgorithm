#include <stdio.h>

int main () {
    int a[10] = {6, 4, 5, 7, 2, 3, 9, 8};
    for(int i = 0; i < 8; i++) {
        int k = i;
        for(int j = i + 1; j < 8; j++) {
            if(a[j] < a[k]) {
                k = j;
            }
        }
        int temp = a[i];
        a[i] = a[k];
        a[k] = temp;
    }

    for(int i = 0; i < 8; i++) {
        printf("%d", a[i]);
    }

    return 0;
}