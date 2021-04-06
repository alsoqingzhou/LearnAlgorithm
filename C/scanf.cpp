#include <stdio.h>
int main() {
    int a, b;
    char c;
    char str[6];
    scanf("%d%d%c%s", &a, &b,&c, str);
    printf("a=%d,b=%d,c=%c,str=%s", a, b, c, str);
    return 0;
}