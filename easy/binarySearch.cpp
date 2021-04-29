#include <stdio.h>

int binarySearch(int A[], int left, int right, int x) {
    int mid;
    while(left <= right) {
        mid = (left + right) / 2;
        if(A[mid] == x) {
            return mid;
        } else if(A[mid] < x){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n;
    int array[10010];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    printf("%d", binarySearch(array, 0, n - 1, 6));

    return 0;
}