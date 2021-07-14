#include <stdio.h>
#include <iostream>
using namespace std;
const int maxsize = 50;

// Q8.3.3-2 双向冒泡排序算法
// 实现思想：奇数趟，从前向后冒泡，将大数向后冒。偶数趟从后向前冒，将小数向前冒
void doubleBubbleSort(int a[], int n) {
    int low = 0, high = n - 1; //两个方向冒泡的边界，一段冒出一个数后边界相应缩小
    bool flag = true; //标记本趟是否有冒出，没有则说明已经有序，跳出循环
    while(low < high && flag) {
        flag = false; //标记初始化
        // 本趟从前向后冒出大数
        for(int i = low; i < high; ++i) { //每趟冒泡都在边界内进行
            if(a[i] > a[i+1]) {
                swap(a[i], a[i+1]); //有逆序，交换
                flag = true;
            }
        }
        //本趟冒泡完毕，边界收缩一
        --high;
        // 本趟从后向前冒出小数
        for(int i = high; i > low; --i) {
            if(a[i] < a[i-1]) {
                swap(a[i], a[i-1]);
                flag = true;
            }
        }
        ++low;
    }
}