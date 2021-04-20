#include <cstdio>
const int maxn = 10010;
bool hashTable[maxn] = {false};

int main() {
    int n, m, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        hashTable[x] = true;
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &x);
        if(hashTable[x]) {printf("Yes, exist");}
        else {printf("No");}
    }
    return 0;
}