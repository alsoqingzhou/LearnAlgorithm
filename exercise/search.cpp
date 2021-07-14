#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

// Q7.2.4-6 折半查找的递归实现
typedef struct {
    int *a;
    int length;
} SSTable;

int biSearch_recursive(SSTable st, int low, int high, int key) {
    while(low < high) {
        int mid = (low + high) / 2;
        if(st.a[mid] == key) {
            return mid;
        } else if(st.a[mid] < key) { //对左边二分查找
            biSearch_recursive(st, low, mid-1, key);
        } else { //对右边二分查找
            biSearch_recursive(st, mid+1, high, key);
        }
    }
    return 0; //跳出循环，查找失败
}
