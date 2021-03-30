#include <stdio.h>
// int main() {
//     int n;
//     scanf("%d", &n);
//     if (n != 0)
//     {
//         printf("n is not equal to 0");
//     }
//     if (n == 0)
//     {
//         printf("n is equal to 0");
//     }
//     return 0;
// }

// another way
int main() {
    int n;
    scanf("%d", &n);
    if (n) //1
    {
        printf("n is not equal to 0");
    }
    if (!n) // !0 = 1
    {
        printf("n is equal to 0");
    }
    return 0;
}