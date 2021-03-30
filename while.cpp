#include <stdio.h>
// give a number, count each number in it together
int main() {
    int n, count = 0;
    scanf("%d", &n);
    while(n) {
        count = count + n % 10; // first time count=5
        // next time count=4
        n = n / 10;
    }
    printf("%d", count);
    return 0;
}