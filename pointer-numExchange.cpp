#include <stdio.h>

//you can define a int number;
// void swap(int *p, int *q) {
//     int temp = *p;
//     *p = *q;
//     *q = temp;
// }

//can also define a point
// void swap(int *p, int *q) {
//     int x;
//     int *temp = &x;
//     *temp = *p;
//     *p = *q;
//     *q = *temp;
// }

// can also used reference
void swap(int* &x, int* &y) {
    int* temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 1, b = 2;
    int *p1 = &a, *p2 = &b;
    swap(p1, p2);
    printf("a = %d\n", *p1);
    printf("b = %d\n", *p2);

    return 0;
}