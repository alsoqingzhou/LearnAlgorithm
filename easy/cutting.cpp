#include <stdio.h>

int cutting(int min, int max, int K, int a[], int N) {
    int mid;

    while(min < max) {
        mid = (min + max) / 2;
        int num = 0;
        for(int i = 0; i < N; i++) {
            num += a[i] / mid;
        }

        if(num < K) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }
    return min - 1;
}

int main() {
    int N, K, a[10];
    scanf("%d %d", &N, &K);

    for(int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    printf("%d", cutting(0, a[N-1], K, a, N));
    
    return 0;
}