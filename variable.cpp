#include <stdio.h>
// int main() {
//     int a = 123456789; // can be printed right
//     int b = 12345678999; // cannot be printed right

//     double c = 3.1415926536;
//     float d = 3.1415;

//     char c1 = 'a', c2 = 'b', c3 = 117;

//     char str1[25] = "hello, i am also";
//     char str2[25] = "nice to meet you";

//     // printf("%d\n%d\n", a, b);
//     // printf("%f\n%f\n", c, d );
//     // printf("%c%c%c", c1, c2, c3);
//     // printf("%c%c\0%c", c1, c2, c3); // c3 will not be shown
//     printf("%s, %s", str1, str2);
//     return 0;
// }

// type convert
// int main() {
//     double r = 12.56;
//     int a = 13, b = 5;
//     printf("%d\n", int(r));
//     printf("%d\n", a / b);
//     printf("%.2f", (double)a / (double)b); //2 means keep two decimal places
//     return 0;
// }

// macro definition
// #define pi 3.14
// const double pi = 3.14; // another way
// int main() {
//     double r = 3;
//     printf("%.2f\n", pi * r * r);
//     return 0;
// }

// another use of #define,but not suggest
// #define ADD(a, b) ((a) + (b))
// int main() {
//     int num1 = 3, num2 = 5;
//     printf("%d", ADD(num1,num2));
//     return 0;
// }

//this example shows the reason
#define cal(x) (x * 2 + 1)
int main() {
    int a = 1;
    printf("%d\n", cal(a + 1)); // get 4, not 5
    // cal(a + 1) will be cal(a + 1 * 2 + 1) not cal((a+1) * 2 + 1)
    return 0;
}