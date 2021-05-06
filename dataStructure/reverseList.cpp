#include <stdio.h>
int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

//反转数组中某个区间的数
void reverse(int a[], int left, int right) {
    for(int i = left, j = right; i < j; i++, j--) {
        int temp;
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

//反转前k个到数组后端
void reverseK(int a[], int k, int length) {
    int left = 0, right = length-1;
    int temp;
    for(int i = left, j = right; i < left+k && i < j; i++, j--) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

//后移前k个元素
void moveBack(int a[], int k, int length) {
    reverse(a, 0, k-1);
    reverse(a, k, length - 1);
    reverse(a, 0, length-1);
}

int main() {
    // reverseK(a, 3, 10);
    moveBack(a, 3, 10);
    for(int i = 0; i < 10; i++) {
        printf("%d", a[i]);
    }
    return 0;
}