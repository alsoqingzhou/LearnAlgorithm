#include <cstdio>
const int maxn = 10010;
int hashTable[maxn] = {0};

int main() {
    int n, m, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        hashTable[x]++;
    }

    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &x);
        if(hashTable[x] > 0) {
            printf("the %d time", hashTable[x]);
            hashTable[x]++;
        } else {
            printf("the first show in n or m");
            hashTable[x] += 2;
        }
    }

    return 0;
}