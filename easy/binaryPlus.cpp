#include <stdio.h>
// [left, right] is [0, n]

// find the first num that >= x
int lowerBound(int A[], int left, int right, int x) {
    int mid;
    while(left < right) { // left==right means find the position
        mid = (left + right) / 2;
        if(A[mid] >= x) { // x at mid or left
            right = mid;
        } else { // x at the right of mid
            left = mid + 1;
        }
    }
    return left;
}

// find the first num that > x
int upperBound(int A[], int left, int right, int x) {
    int mid;
    while(left < right) {
        mid = (left + right) / 2;
        if(A[mid] > x) { // x at mid or left 
            right = mid;
        } else { // x at the right of mid
            left = mid + 1;
        }
    }
    return left;
}

// the model of find the first element that
//satisfies the condition in the sequence of ordinal numbers
int findSth(int A[], int left, int right) {
    int mid;
//     while(left < right) {
//         mid = (left + right) / 2;
//         if(satisfies) { //the first <= mid
//             right = mid; //
//         } else { // the fist > mid
//             left = mid;
//         }
//     }
//     return left;
}