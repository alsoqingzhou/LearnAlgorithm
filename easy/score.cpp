#include <cstdio>

const int maxn = 100010;
int school[maxn] = {0};

int main() {
    int n, ID, score;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &ID, &score);
        school[ID] += score;
    }

    int k, MAX = -1;
    for(int i = 0; i <= n; i++) {
        if(school[i] > MAX) {
            k = i;
            MAX = school[i];
        }
    }
    printf("%d %d", k, MAX);

    return 0;
}
