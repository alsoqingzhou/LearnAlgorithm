#include <stdio.h>

int main() {
    int a[10] = {6, 4, 5, 7, 2, 3, 9, 8};
    for(int i = 1; i < 8; i++) { //进行n-1趟排序
        int temp = a[i], j = i;
        while(j > 0 && temp < a[j - 1]) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;
    }

    for(int i = 0; i < 8; i++) {
        printf("%d", a[i]);
    }

    return 0;
}