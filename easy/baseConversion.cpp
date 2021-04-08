#include <stdio.h>

int main() {
    int a, b, d;
    scanf("%d %d %d", &a, &b, &d);
    int sum = a + b;
    int z[40], num = 0;

    do {
        z[num++] = sum % d;
        sum = sum / d;
    } while(sum != 0);

    for(int i = num - 1; i >= 0; i--) {
        printf("%d", z[i]);
    }

    return 0;
}