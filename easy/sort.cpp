#include <stdio.h>
#include <algorithm>
using namespace std;

bool cmp(char a, char b) {
    return a < b;
}

int main() {
    int a[6] = {3, 6, 6, 8, 3, 9};
    sort(a, a + 7);

    double b[] = {1.2, 3.5, 1.6};
    sort(b, b + 4);

    char c[] = {'a', 'c', 'b'};
    sort(c, c + 4, cmp);

    for(int i = 0; i < 3; i++) {
        printf("%c", c[i]);
    }

    return 0;
}