#include <stdio.h>
// sum odd numbers less than n
int main () {
    int n, sum;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        if (i % 2 != 1) // n is even number
        {
            continue; // jump out of the loop
        }
        sum = sum + i;
    }
    printf("%d", sum);
    return 0;
}