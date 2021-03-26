#include <stdio.h>
int main() {
    int a = 123456789; // can be printed right
    int b = 12345678999; // cannot be printed right

    double c = 3.1415926536;
    float d = 3.1415;

    char c1 = 'a', c2 = 'b', c3 = 117;

    char str1[25] = "hello, i am also";
    char str2[25] = "nice to meet you";

    // printf("%d\n%d\n", a, b);
    // printf("%f\n%f\n", c, d );
    // printf("%c%c%c", c1, c2, c3);
    // printf("%c%c\0%c", c1, c2, c3); // c3 will not be shown
    printf("%s, %s", str1, str2);
}