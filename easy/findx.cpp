#include <cstdio>

const int maxn = 200;
int a[maxn];

int main() {
    int n, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++ ){
        scanf("%d", &a[i]);
    }
    
    scanf("%d", &x);
    int k;
    for(k = 0; k < n; k++) {
        if(a[k] == x) {
            printf("%d", k);
            break;
        }
    }
    if(k == n) {
        printf("-1");
    } 

    return 0;
}