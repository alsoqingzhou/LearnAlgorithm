#include <stdio.h>
void change(int x){
    x = x + 1;
}

int main() {
    int x = 10;
    change(x);
    printf("%d", x);
    return 0;
}