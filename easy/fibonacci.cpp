#include <stdio.h>
int Fb(int n) {
    if(n == 1 || n == 2) {return 1;}
    else {
        return (Fb(n-1) + Fb(n-2));
    }

}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", Fb(n));
    return 0;
}

